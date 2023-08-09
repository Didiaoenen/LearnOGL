#include "GraphicsManager.h"

#include "BaseApplication.h"
#include "BRDFIntegrator.h"
#include "SceneManager.h"

#include "ForwardGeometryPass.h"
#include "ShadowMapPass.h"
#include "OverlayPass.h"

#include "SceneObjectCamera.h"

using namespace OGL;
using namespace std;
using namespace glm;

GraphicsManager::GraphicsManager() 
{
    mFrames.resize(GfxConfiguration::kMaxInFlightFrameCount);
}

bool GraphicsManager::Initialize()
{
    const GfxConfiguration& conf = mApp->GetConfiguration();

    auto app = static_cast<BaseApplication*>(mApp);
    auto pipelineStateManager = app->GetModule<IPipelineStateManager>();

    if (pipelineStateManager)
    {
        mInitPasses.push_back(make_shared<BRDFIntegrator>(this, pipelineStateManager));
        mDrawPasses.push_back(make_shared<ShadowMapPass>(this, pipelineStateManager));

        auto forward_pass = make_shared<ForwardGeometryPass>(this, pipelineStateManager);
        forward_pass->EnableRenderToTexture();

        mDrawPasses.push_back(forward_pass);
        mDrawPasses.push_back(make_shared<OverlayPass>(this, pipelineStateManager));
    }

    InitConstants();

    mInitialize = true;

    return false;
}

void GraphicsManager::Finalize()
{
    EndScene();
}

void GraphicsManager::Tick()
{
    auto app = static_cast<BaseApplication*>(mApp);
    auto sceneManager = app->GetModule<SceneManager>();

    if (sceneManager)
    {
        auto rev = sceneManager->GetSceneRevision();
        if (!rev)
            return;

        if (mSceneRevision < rev) 
        {
            EndScene();
            const auto scene = sceneManager->GetSceneForRendering();
            assert(scene);
            BeginScene(*scene);
            mSceneRevision = rev;
        }
    }

    UpdateConstants();

    BeginFrame(mFrames[mFrameIndex]);
    Draw();
    EndFrame(mFrames[mFrameIndex]);

    Present();
}

void GraphicsManager::Draw()
{
    auto& frame = mFrames[mFrameIndex];

    for (auto& pDispatchPass : mDispatchPasses) 
    {
        pDispatchPass->BeginPass(frame);
        pDispatchPass->Dispatch(frame);
        pDispatchPass->EndPass(frame);
    }

    for (auto& pDrawPass : mDrawPasses) 
    {
        pDrawPass->BeginPass(frame);
        pDrawPass->Draw(frame);
        pDrawPass->EndPass(frame);
    }
}

void GraphicsManager::BeginScene(const Scene& scene)
{
    for (const auto& pPass : mInitPasses) 
    {
        pPass->BeginPass(mFrames[0]);
        pPass->Dispatch(mFrames[0]);
        pPass->EndPass(mFrames[0]);
    }

    if (!mFrames[0].frameContext.shadowMap.handler) 
    {
        mFrames[0].frameContext.shadowMap.width = GfxConfiguration::kShadowMapWidth;
        mFrames[0].frameContext.shadowMap.height = GfxConfiguration::kShadowMapHeight;
        mFrames[0].frameContext.shadowMap.size = GfxConfiguration::kMaxShadowMapCount;
        GenerateTextureArray(mFrames[0].frameContext.shadowMap);
    }

    if (!mFrames[0].frameContext.globalShadowMap.handler) 
    {
        mFrames[0].frameContext.globalShadowMap.width = GfxConfiguration::kShadowMapWidth;
        mFrames[0].frameContext.globalShadowMap.height = GfxConfiguration::kShadowMapHeight;
        mFrames[0].frameContext.globalShadowMap.size = GfxConfiguration::kMaxShadowMapCount;
        GenerateTextureArray(mFrames[0].frameContext.globalShadowMap);
    }

    if (!mFrames[0].frameContext.cubeShadowMap.handler) 
    {
        mFrames[0].frameContext.cubeShadowMap.width = GfxConfiguration::kShadowMapWidth;
        mFrames[0].frameContext.cubeShadowMap.height = GfxConfiguration::kShadowMapHeight;
        mFrames[0].frameContext.cubeShadowMap.size = GfxConfiguration::kMaxShadowMapCount;
        GenerateCubemapArray(mFrames[0].frameContext.cubeShadowMap);
    }

    if (scene.mGeometries.size()) 
    {
        InitializeGeometries(scene);
    }
    if (scene.mSkyBox) 
    {
        InitializeSkyBox(scene);
    }

    for (int32_t i = 0; i < GfxConfiguration::kMaxInFlightFrameCount; i++) 
    {
        mFrames[i] = mFrames[0];
        mFrames[i].frameIndex = i;
    }

    CreateFrameBuffers();
}

void GraphicsManager::EndScene()
{
    for (auto& texture : mTextures) 
    {
        ReleaseTexture(texture);
    }

    for (auto& frame : mFrames) 
    {
        for (auto& texture : frame.colorTextures) 
        {
            ReleaseTexture(texture);
        }

        ReleaseTexture(frame.depthTexture);
    }
}

void GraphicsManager::CalculateCameraMatrix()
{
    auto app = static_cast<BaseApplication*>(mApp);
    auto sceneManager = app->GetModule<SceneManager>();

    if (sceneManager)
    {
        auto& scene = sceneManager->GetSceneForRendering();
        auto cameraNode = scene->GetFirstCameraNode();
        DrawFrameContext& frameContext = mFrames[mFrameIndex].frameContext;
        if (cameraNode)
        {
            auto transform = *cameraNode->GetCalculatedTransform();
            glm::vec3 position = glm::vec3({ transform[3][0], transform[3][1], transform[3][2] });
            glm::vec3 lookAt = cameraNode->GetTarget();
            glm::vec3 up = { 0.0f, 0.0f, 1.0f };
            frameContext.viewMatrix = glm::lookAt(position, lookAt, up);
            frameContext.camPos = { position[0], position[1], position[2], 0.0f };
        }
        else 
        {
            glm::vec3 position = { 0.0f, -5.0f, 0.0f };
            glm::vec3 lookAt = { 0.0f, 0.0f, 0.0f };
            glm::vec3 up = { 0.0f, 0.0f, 1.0f };
            frameContext.viewMatrix = glm::lookAt(position, lookAt, up);
        }

        float fieldOfView = glm::pi<float>() / 3.0f;
        float nearClipDistance = 10.0f;
        float farClipDistance = 100.0f;

        if (cameraNode)
        {
            auto camera = scene->GetCamera(cameraNode->GetSceneObjectRef());
            fieldOfView = dynamic_pointer_cast<SceneObjectPerspectiveCamera>(camera)->GetFov();
            nearClipDistance = camera->GetNearClipDistance();
            farClipDistance = camera->GetFarClipDistance();
        }

        float screenAspect = (float)mCanvasWidth / (float)mCanvasHeight;

        frameContext.projectionMatrix = glm::perspective(fieldOfView, screenAspect, nearClipDistance, farClipDistance);
    }
}

void GraphicsManager::CalculateLights()
{
    DrawFrameContext& frameContext = mFrames[mFrameIndex].frameContext;
    auto& lightInfo = mFrames[mFrameIndex].lightInfo;

    auto app = static_cast<BaseApplication*>(mApp);
    auto pSceneManager = app->GetModule<SceneManager>();

    const GfxConfiguration& conf = mApp->GetConfiguration();

    frameContext.numLights = 0;
    frameContext.clipSpaceType = 1;

    if (pSceneManager) 
    {
        auto& scene = pSceneManager->GetSceneForRendering();
        for (const auto& lightNode : scene->mLightNodes)
        {
            Light& light = lightInfo.lights[frameContext.numLights];
            auto pLightNode = lightNode.second;
            if (!pLightNode) 
                continue;
            
            auto transPtr = pLightNode->GetCalculatedTransform();
            light.lightPosition = { 0.0f, 0.0f, 0.0f, 1.0f };
            light.lightDirection = { 0.0f, 0.0f, -1.0f, 0.0f };
            translate(*transPtr, vec3(light.lightPosition));
            translate(*transPtr, vec3(light.lightDirection));
            normalize(light.lightDirection);

            auto pLight = scene->GetLight(pLightNode->GetSceneObjectRef());
            if (pLight) 
            {
                /*light.lightGuid = pLight->GetGuid();
                light.lightColor = pLight->GetColor().Value;
                light.lightIntensity = pLight->GetIntensity();
                light.lightCastShadow = pLight->GetIfCastShadow();
                const AttenCurve& atten_curve = pLight->GetDistanceAttenuation();
                light.lightDistAttenCurveType = atten_curve.type;
                memcpy(light.lightDistAttenCurveParams, &atten_curve.u, sizeof(atten_curve.u));
                light.lightAngleAttenCurveType = AttenCurveType::kNone;

                glm::mat4x4 view;
                glm::mat4x4 projection;
                BuildIdentityMatrix(projection);

                float nearClipDistance = 1.0f;
                float farClipDistance = 1000.0f;

                if (pLight->GetType() == SceneObjectType::kSceneObjectTypeLightInfi) 
                {
                    light.lightType = LightType::Infinity;

                    glm::vec4 target = { 0.0f, 0.0f, 0.0f, 1.0f };

                    auto pCameraNode = scene->GetFirstCameraNode();
                    if (pCameraNode) 
                    {
                        auto pCamera = scene->GetCamera(pCameraNode->GetSceneObjectRef());
                        nearClipDistance = pCamera->GetNearClipDistance();
                        farClipDistance = pCamera->GetFarClipDistance();

                        target[2] = -(0.75f * nearClipDistance + 0.25f * farClipDistance);

                        auto trans_ptr = pCameraNode->GetCalculatedTransform();
                        Transform(target, *trans_ptr);
                    }

                    light.lightPosition = target - light.lightDirection * farClipDistance;
                    glm::vec3 position(light.lightPosition);
                    glm::vec3 lookAt(target);
                    glm::vec3 up = { 0.0f, 0.0f, 1.0f };
                    if (abs(light.lightDirection[0]) <= 0.2f && abs(light.lightDirection[1]) <= 0.2f)
                    {
                        up = { 0.1f, 0.1f, 1.0f };
                    }
                    BuildViewRHMatrix(view, position, lookAt, up);

                    float sm_half_dist = min(farClipDistance * 0.25f, 800.0f);

                    if (conf.fixOpenGLPerspectiveMatrix) 
                    {
                        BuildOpenglOrthographicRHMatrix(projection, -sm_half_dist, sm_half_dist, sm_half_dist, -sm_half_dist, nearClipDistance, farClipDistance + sm_half_dist);
                    }
                    else 
                    {
                        BuildOrthographicRHMatrix(projection, -sm_half_dist, sm_half_dist, sm_half_dist, -sm_half_dist, nearClipDistance, farClipDistance + sm_half_dist);
                    }

                    light.lightPosition[3] = 0.0f;
                }
                else 
                {
                    glm::vec3 position(light.lightPosition);
                    glm::vec3 lookAt(light.lightPosition + light.lightDirection);
                    glm::vec3 up = { 0.0f, 0.0f, 1.0f };
                    if (abs(light.lightDirection[0]) <= 0.1f && abs(light.lightDirection[1]) <= 0.1f) 
                    {
                        up = { 0.0f, 0.707f, 0.707f };
                    }
                    BuildViewRHMatrix(view, position, lookAt, up);

                    if (pLight->GetType() == SceneObjectType::kSceneObjectTypeLightSpot) 
                    {
                        light.lightType = LightType::Spot;

                        auto plight = dynamic_pointer_cast<SceneObjectSpotLight>(pLight);
                        const AttenCurve& angle_atten_curve = plight->GetAngleAttenuation();
                        light.lightAngleAttenCurveType = angle_atten_curve.type;
                        memcpy(light.lightAngleAttenCurveParams, &angle_atten_curve.u, sizeof(angle_atten_curve.u));

                        float fieldOfView = light.lightAngleAttenCurveParams[0][1] * 2.0f;
                        float screenAspect = 1.0f;

                        if (conf.fixOpenGLPerspectiveMatrix) 
                        {
                            BuildOpenglPerspectiveFovRHMatrix(projection, fieldOfView, screenAspect, nearClipDistance, farClipDistance);
                        }
                        else 
                        {
                            BuildPerspectiveFovRHMatrix(projection, fieldOfView, screenAspect, nearClipDistance, farClipDistance);
                        }
                    }
                    else if (pLight->GetType() == SceneObjectType::kSceneObjectTypeLightArea) 
                    {
                        light.lightType = LightType::Area;

                        auto plight = dynamic_pointer_cast<SceneObjectAreaLight>(pLight);
                        light.lightSize = plight->GetDimension();
                    }
                    else
                    {
                        light.lightType = LightType::Omni;

                        float fieldOfView = glm::pi<float>() / 2.0f;
                        float screenAspect = 1.0f;

                        if (conf.fixOpenGLPerspectiveMatrix) 
                        {
                            BuildOpenglPerspectiveFovRHMatrix(projection, fieldOfView, screenAspect, nearClipDistance, farClipDistance);
                        }
                        else 
                        {
                            BuildPerspectiveFovRHMatrix(projection, fieldOfView, screenAspect, nearClipDistance, farClipDistance);
                        }
                    }
                }

                light.lightViewMatrix = view;
                light.lightProjectionMatrix = projection;
                frameContext.numLights++;*/
            }
        }
    }
}

void GraphicsManager::UpdateConstants()
{
    auto& frame = mFrames[mFrameIndex];

    for (auto& pDbc : frame.batchContexts) 
    {
        pDbc->modelMatrix = *pDbc->node->GetCalculatedTransform();
    }

    CalculateCameraMatrix();
    CalculateLights();
}

void GraphicsManager::CreateFrameBuffers()
{
    auto conf = mApp->GetConfiguration();

    for (int32_t i = 0; i < GfxConfiguration::kMaxInFlightFrameCount; i++) 
    {
        for (int32_t j = 0; j < mFrames[i].colorTextures.size(); j++) 
        {
            if (j == 0) 
            {
                ReleaseTexture(mFrames[i].colorTextures[0]);
            }
            else 
            {
                if (i == 0) 
                {
                    ReleaseTexture(mFrames[0].colorTextures[j]);
                }
            }
        }

        mFrames[i].colorTextures.clear();
    }

    if (mFrames[0].depthTexture.handler) 
    {
        ReleaseTexture(mFrames[0].depthTexture);
    }

    for (int32_t i = 0; i < GfxConfiguration::kMaxInFlightFrameCount; i++) 
    {
        Texture2D colorTexture;
        colorTexture.width = mCanvasWidth;
        colorTexture.height = mCanvasHeight;
        colorTexture.pixelFormat = PixelFormat::RGBA8;
        colorTexture.mips = 1;
        colorTexture.samples = 0;

        GenerateTexture(colorTexture);

        mFrames[i].colorTextures.push_back(colorTexture);

        if (i == 0) 
        {
            if (conf.msaaSamples > 1) 
            {
                colorTexture.samples = conf.msaaSamples;
                GenerateTexture(colorTexture);
                mFrames[0].colorTextures.push_back(colorTexture);
                mFrames[0].enableMSAA = false;
            }

            Texture2D depthbuffer;
            depthbuffer.width = mCanvasWidth;
            depthbuffer.height = mCanvasHeight;
            depthbuffer.pixelFormat = PixelFormat::R8;
            depthbuffer.mips = 1;
            depthbuffer.samples = conf.msaaSamples;

            GenerateTexture(depthbuffer);

            mFrames[0].depthTexture = depthbuffer;
        }
        else 
        {
            mFrames[i].colorTextures.push_back(mFrames[0].colorTextures[0]);
            mFrames[i].depthTexture = mFrames[0].depthTexture;
            mFrames[i].enableMSAA = mFrames[0].enableMSAA;
        }
    }
}
