#include "StringUtils.h"

#include "State.h"

#include "ogl.h"

CState::CState()
{
}

CState::~CState()
{
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