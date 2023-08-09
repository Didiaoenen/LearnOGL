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
                //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, (GLuint)frame.colorTextures[0].handler, 0);
            
                //unsigned int textureColorbuffer;
                //glGenTextures(1, &textureColorbuffer);
                //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
                //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

                {
                    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                }

                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + 0, GL_TEXTURE_2D, (GLuint)frame.colorTextures[0].handler, 0);
            }
        }

        if (frame.depthTexture.handler)
        {
            //glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, (GLuint)frame.depthTexture.handler, 0);
            
            //unsigned int rbo;
            //glGenRenderbuffers(1, &rbo);
            //glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 512, 512);
            //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

            {
                //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }

            unsigned int id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 512, 512, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, id, 0);

            glBindTexture(GL_TEXTURE_2D, 0);
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