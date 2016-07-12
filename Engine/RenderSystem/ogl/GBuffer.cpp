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
        ogl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mRenderTargets[i], 0);
    }

    // depth
    glBindTexture(GL_TEXTURE_2D, mDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, aWindowWidth, aWindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 NULL);
    ogl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepth, 0);

    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    ogl::glDrawBuffers(eGBT_Count, DrawBuffers);

    GLenum Status = ogl::glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("FB error, status: 0x%x\n", Status);
    }

    // restore default FBO
    ogl::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    ogl::CheckOGLError("After GBuffer Creation");
}

const uint32* CGBuffer::GetRenderTargets() const
{
    return &mRenderTargets[0];
}

void CGBuffer::Bind()
{
    ogl::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mID);
}