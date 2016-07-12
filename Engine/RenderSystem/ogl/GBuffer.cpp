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

static const uint32 SCR_WIDTH = 800;
static const uint32 SCR_HEIGHT = 600;

void CGBuffer::Create()
{
    ogl::glGenFramebuffers(1, &mID);
    ogl::glBindFramebuffer(GL_FRAMEBUFFER, mID);

    // - Color + Specular color buffer
    glGenTextures(1, &mRenderTargets[0]);
    glBindTexture(GL_TEXTURE_2D, mRenderTargets[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ogl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mRenderTargets[0], 0);

    // - Position color buffer
    glGenTextures(1, &mRenderTargets[1]);
    glBindTexture(GL_TEXTURE_2D, mRenderTargets[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ogl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mRenderTargets[1], 0);

    // - Normal color buffer
    glGenTextures(1, &mRenderTargets[2]);
    glBindTexture(GL_TEXTURE_2D, mRenderTargets[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    ogl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mRenderTargets[2], 0);

    // - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    ogl::glDrawBuffers(3, attachments);

    // - Create and attach depth buffer (renderbuffer)
    ogl::glGenRenderbuffers(1, &mRenderTargets[3]);
    ogl::glBindRenderbuffer(GL_RENDERBUFFER, mRenderTargets[3]);
    ogl::glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    ogl::glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderTargets[3]);

    // - Finally check if framebuffer is complete
    if (ogl::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("Framebuffer not complete!");
    }

    ogl::glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CGBuffer::Bind()
{
    ogl::glBindFramebuffer(GL_FRAMEBUFFER, mID);
}