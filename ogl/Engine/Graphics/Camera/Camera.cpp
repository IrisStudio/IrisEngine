#include "Camera.h"
#include "Mth.h"

CCamera::CCamera()
{

}

CCamera::CCamera( ECameraType aType )
  : mType(aType)
{

}

CCamera::~CCamera()
{

}

void CCamera::SetPosition(const float3& aPosition)
{
  mPosition = aPosition;
}

const float3& CCamera::GetPosition() const
{
  return mPosition;
}

void CCamera::SetLookAt(const float3& aLookAt)
{
  mLookAt = aLookAt;
}

const float3& CCamera::GetLookAt() const
{
  return mLookAt;
}

const float3& CCamera::GetDirection() const
{
  return mDirection;
}

void  CCamera::SetFOV(float aFOV)
{
  mFOV = aFOV;
}

float CCamera::GetFOV() const
{
  return mFOV;
}

void  CCamera::SetClipPlanes(float aFar, float aNear)
{
  mNearClip = aNear;
  mFarClip = aFar;
}

void CCamera::GetClipPlanes(float& aFar, float& aNear) const
{
  aFar = mFarClip;
  aNear = mNearClip;
}

void  CCamera::SetViewport(uint32 aPosX, uint32 aPosY, uint32 aWidth, uint32 aHeight)
{
  mViewportX = aPosX;
  mViewportY = aPosY;
  mViewportWidth = aWidth;
  mViewportHeight = aHeight;
}

void  CCamera::GetViewport(uint32 &aPosX, uint32 &aPosY, uint32 &aWidth, uint32 &aHeight)
{
  aPosX = mViewportX;
  aPosY = mViewportY;
  aWidth = mViewportWidth;
  aHeight = mViewportHeight;
}

void  CCamera::GetMatricies(float4x4 &P, float4x4 &V, float4x4 &M) const
{

}

void  CCamera::ChangeYaw(float aDeg)
{

}

void  CCamera::ChangePitch(float aDeg)
{

}

void CCamera::Update()
{
  mDirection = mth::normalize(mLookAt - mPosition);
}