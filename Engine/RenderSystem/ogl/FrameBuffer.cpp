#include "FrameBuffer.h"

#include "Logger/Logger.h"

#include "State.h"
#include "GBuffer.h"
#include "ogl.h"

CFrameBuffer::CFrameBuffer()
    : mID(0)
{

}

CFrameBuffer::~CFrameBuffer()
{

}

void CFrameBuffer::Create()
{
}

void CFrameBuffer::Bind()
{
    ogl::glBindFramebuffer(GL_FRAMEBUFFER, mID);
}

void CFrameBuffer::Blit(CGBuffer& aGBuffer, uint32 aWindowWidth, uint32 aWindowHeight )
{
    CState::ClearBuffers(float4(0), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    aGBuffer.LightingPass();

    uint32 HalfWidth = (uint32)(aWindowWidth * 0.5f);
    uint32 HalfHeight = (uint32)(aWindowHeight * 0.5f);

    aGBuffer.BindBuffer(CGBuffer::eGBT_AlbedoSpec);
    ogl::glBlitFramebuffer(0, 0, aWindowWidth, aWindowHeight, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    aGBuffer.BindBuffer(CGBuffer::eGBT_WorldSpacePosition);
    ogl::glBlitFramebuffer(0, 0, aWindowWidth, aWindowHeight,
                           0, HalfHeight, HalfWidth, aWindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    aGBuffer.BindBuffer(CGBuffer::eGBT_WorldSpaceNormal);
    ogl::glBlitFramebuffer(0, 0, aWindowWidth, aWindowHeight,
                           HalfWidth, HalfHeight, aWindowWidth, aWindowHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    /*ogl::CheckOGLError("Before depth blit");
    glReadBuffer(GL_DEPTH_ATTACHMENT);
    ogl::glBlitFramebuffer(0, 0, aWindowWidth, aWindowHeight,
                           HalfWidth, 0, aWindowWidth, HalfHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    ogl::CheckOGLError("after depth blit"); */
}