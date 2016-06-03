#include "StringUtils.h"

#include "State.h"

#include "ogl.h"

namespace
{
    static bool          mBlend;
    static BlendEquation mBlendEquation;
    static BlendFunc     mBlendFuncSrc;
    static BlendFunc     mBlendFuncDst;
    static bool          mCullFace;
    static bool          mDepthTest;
    static bool          mScissorTest;
    static uint2         mViewportPos;
    static uint2         mViewportSize;

    static const GLenum sTextureStageId[32] =
    {
        GL_TEXTURE0,
        GL_TEXTURE1,
        GL_TEXTURE2,
        GL_TEXTURE3,
        GL_TEXTURE4,
        GL_TEXTURE5,
        GL_TEXTURE6,
        GL_TEXTURE7,
        GL_TEXTURE8,
        GL_TEXTURE9,
        GL_TEXTURE10,
        GL_TEXTURE11,
        GL_TEXTURE12,
        GL_TEXTURE13,
        GL_TEXTURE14,
        GL_TEXTURE15,
        GL_TEXTURE16,
        GL_TEXTURE17,
        GL_TEXTURE18,
        GL_TEXTURE19,
        GL_TEXTURE20,
        GL_TEXTURE21,
        GL_TEXTURE22,
        GL_TEXTURE23,
        GL_TEXTURE24,
        GL_TEXTURE25,
        GL_TEXTURE26,
        GL_TEXTURE27,
        GL_TEXTURE28,
        GL_TEXTURE29,
        GL_TEXTURE30,
        GL_TEXTURE31
    };
}

void CState::SetBlendEquation(const BlendEquation aBlendEquation)
{
    if (aBlendEquation != mBlendEquation)
    {
        mBlendEquation = aBlendEquation;
        ogl::glBlendEquation(mBlendEquation);
    }
}
void CState::SetBlendFunc(const BlendFunc aBlendFuncSrc, const BlendFunc aBlendFuncDst)
{
    if (aBlendFuncSrc != mBlendFuncSrc || aBlendFuncDst != mBlendFuncDst)
    {
        mBlendFuncSrc = aBlendFuncSrc;
        mBlendFuncDst = aBlendFuncDst;
        glBlendFunc(mBlendFuncSrc, mBlendFuncDst);
    }
}

void CState::EnableBlend()
{
    if (!mBlend)
    {
        mBlend = true;
        glEnable(GL_BLEND);
    }
}

void CState::EnableCullFace()
{
    if (!mCullFace)
    {
        mCullFace = true;
        glEnable(GL_CULL_FACE);
    }
}

void CState::EnableDepthTest()
{
    if (!mDepthTest)
    {
        mDepthTest = true;
        glEnable(GL_DEPTH_TEST);
    }
}

void CState::EnableScissorTest()
{
    if (!mScissorTest)
    {
        mScissorTest = true;
        glEnable(GL_SCISSOR_TEST);
    }
}

void CState::DisableBlend()
{
    if (mBlend)
    {
        mBlend = false;
        glDisable(GL_BLEND);
    }
}

void CState::DisableCullFace()
{
    if (mCullFace)
    {
        mCullFace = false;
        glDisable(GL_CULL_FACE);
    }
}

void CState::DisableDepthTest()
{
    if (mDepthTest)
    {
        mDepthTest = false;
        glDisable(GL_DEPTH_TEST);
    }
}

void CState::DisableScissorTest()
{
    if (mScissorTest)
    {
        mScissorTest = false;
        glDisable(GL_SCISSOR_TEST);
    }
}

void CState::ActivateTexture(uint32 aStageId)
{
    ogl::glActiveTexture(sTextureStageId[aStageId]);
}

void CState::BindTexture(TextureType aType, uint32 aId)
{
    glBindTexture(aType, aId);
}

void CState::SetViewport(uint32 aX, uint32 aY, uint32 aWidth, uint32 aHeight)
{
    if(mViewportPos.x != aX || mViewportPos.y != aY || mViewportSize.x != aWidth || mViewportSize.y != aHeight )
    {
        mViewportPos.x = aX;
        mViewportPos.y = aY;
        mViewportSize.x = aWidth;
        mViewportSize.y = aHeight;
        glViewport(aX, aY, aWidth, aHeight);
    }
}

const bool CState::GetBlend()
{
    return mBlend;
}

const BlendEquation  CState::GetBlendEquation()
{
    return mBlendEquation;
}

const BlendFunc      CState::GetBlendFuncSrc()
{
    return mBlendFuncSrc;
}

const BlendFunc      CState::GetBlendFuncDst()
{
    return mBlendFuncDst;
}

const bool           CState::GetCullFace()
{
    return mCullFace;
}

const bool           CState::GetDepthTest()
{
    return mDepthTest;
}

const bool           CState::GetScissorTest()
{
    return mScissorTest;
}