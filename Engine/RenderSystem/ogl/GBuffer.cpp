#include "GBuffer.h"

#include "Logger/Logger.h"

#include "ogl.h"

CGBuffer::CGBuffer()
    : mID(0)
{
}

CGBuffer::~CGBuffer()
{
}

void CGBuffer::Create(uint32 aWindowWidth, uint32 aWindowHeight)
{
    ogl::CheckOGLError("After GBuffer Creation");

    // Create the FBO
    ogl::glGenFramebuffers(1, &mID);
    ogl::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mID);

    // Create the gbuffer textures
    glGenTextures(eGBT_Count, &mRenderTargets[0]);
    glGenTextures(1, &mDepth);

    for (uint32 i = 0; i < eGBT_Count; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, mRenderTargets[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, aWindowWidth, aWindowHeight, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ogl::glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, mRenderTargets[i], 0);
    }

    glGenTextures(1, &mDepth);
    glBindTexture(GL_TEXTURE_2D, mDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, aWindowWidth, aWindowHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    ogl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepth, 0);

    GLenum DrawBuffers[eGBT_Count] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    ogl::glDrawBuffers(eGBT_Count, DrawBuffers);

    GLenum Status = ogl::glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("FB error, status: 0x%x\n", Status);
    }

    // restore default FBO
    glBindTexture(GL_TEXTURE_2D, 0);
    ogl::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    ogl::CheckOGLError("After GBuffer Creation");
}

const uint32* CGBuffer::GetRenderTargets() const
{
    return &mRenderTargets[0];
}

void CGBuffer::GeometryPass()
{
    ogl::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mID);
}
void CGBuffer::LightingPass()
{
    ogl::glBindFramebuffer(GL_READ_FRAMEBUFFER, mID);
}

void CGBuffer::BindBuffer(ETarget aBufferTarget)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + aBufferTarget);
}