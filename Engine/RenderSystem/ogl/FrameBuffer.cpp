#include "FrameBuffer.h"

#include "Logger/Logger.h"

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