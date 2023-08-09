#include "OpenGLGraphicsManager.h"

#include <iostream>
#include <glad/glad.h>

using namespace OGL;
using namespace std;

bool OpenGLGraphicsManager::Initialize()
{
    if (mInitialize)
    {
        return true;
    }

    OpenGLGraphicsCommonBaseManager::Initialize();

    if (!gladLoadGL())
    {
        cerr << "OpenGL load failed!" << endl;
        return false;
    }

    cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << " loaded" << endl;

    auto conf = mApp->GetConfiguration();
    glViewport(0, 0, conf.screenWidth, conf.screenHeight);

    if (conf.msaaSamples) 
    {
        glEnable(GL_MULTISAMPLE);
    }

    return true;
}

void OpenGLGraphicsManager::Finalize()
{
    OpenGLGraphicsCommonBaseManager::Finalize();
}

void OpenGLGraphicsManager::CreateTextureView(Texture2D& textureView, const TextureArrayBase& textureArray, const uint32_t slice, const uint32_t mip)
{
}

void OpenGLGraphicsManager::BeginPass(Frame& frame)
{
    if (frame.renderToTexture)
    {
        GLuint framebuffer;
        glGenFramebuffers(1, &framebuffer);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        if (frame.enableMSAA)
        {
            if (frame.colorTextures[1].handler)
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, (GLuint)frame.colorTextures[1].handler, 0);
            }
        }
        else 
        {
            if (frame.colorTextures[0].handler) 
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (GLuint)frame.colorTextures[0].handler, 0);
            }
        }

        if (frame.depthTexture.handler)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, frame.depthTexture.handler, 0);
        }

        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) 
        {
            assert(0);
        }

        frame.frameBuffer = framebuffer;
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    glViewport(0, 0, mCanvasWidth, mCanvasHeight);

    if (frame.clearRT)
    {
        glClearColor(frame.clearColor[0], frame.clearColor[1], frame.clearColor[2], frame.clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void OGL::OpenGLGraphicsManager::EndPass(Frame& frame)
{
    if (frame.renderToTexture)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        GLuint framebuffer = (GLuint)frame.frameBuffer;
        glDeleteFramebuffers(1, &framebuffer);

        frame.frameBuffer = 0;
    }
}

void OpenGLGraphicsManager::GetOpenGLTextureFormat(const PixelFormat pixelFormat, uint32_t& format, uint32_t& internalFormat, uint32_t& type)
{
    switch (pixelFormat) 
    {
    case PixelFormat::R8:
        format = GL_RED;
        internalFormat = GL_R8;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::RGB8:
        format = GL_RGB;
        internalFormat = GL_RGB8;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::RGBA8:
        format = GL_RGBA;
        internalFormat = GL_RGBA8;
        type = GL_UNSIGNED_BYTE;
        break;
    case PixelFormat::DEPTH:
        format = GL_DEPTH_COMPONENT;
        internalFormat = GL_DEPTH_COMPONENT;
        type = GL_FLOAT;
        break;
    default:
        break;
    }
}

void OpenGLGraphicsManager::GetOpenGLTextureFormat(const CompressedFormat compressedFormat, uint32_t& format, uint32_t& internalFormat, uint32_t& type)
{
}

void OpenGLGraphicsManager::BeginFrame(Frame& frame)
{
    OpenGLGraphicsCommonBaseManager::BeginFrame(frame);
}

void OpenGLGraphicsManager::EndFrame(Frame& frame)
{
    OpenGLGraphicsCommonBaseManager::EndFrame(frame);
}