#include "Camera.h"
#include "Mth.h"
#include "ogl.h"

CCamera::CCamera()
  : mType( eFree )
  , mPosition( float3(0.0f) )
  , mLookAt( float3(1.0f, 0.0f, 0.0f) )
  , mDirection( float3(0.0f) )
  , mUp(float3(0.0f, 0.0f, 1.0f) )
  , mDelta(float3(0.0f))
  , mRotation(quaternion(1, 0, 0, 0))
  , mAspectRatio( 16.0f / 9.0f )
  , mFOV(60.0f)
  , mNearClip(0.01)
  , mFarClip(1000.0)
  , mViewportX(0)
  , mViewportY(0)
  , mViewportWidth(800)
  , mViewportHeight(600)
  , mMove(false)
{
  mDirection = glm::normalize(mLookAt - mPosition);
  mYaw       = mth::ATan2(mDirection.z, mDirection.x);
  mPitch     = mth::ATan2(mDirection.y, mth::Sqrt(mDirection.z * mDirection.z + mDirection.x * mDirection.x));
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
  mDirection = glm::normalize(mLookAt - mPosition);
  switch (mType)
  {
  case eOrtho:
  {
    mProjection = glm::ortho(-1.5f * float(mAspectRatio), 1.5f * float(mAspectRatio), -1.5f, 1.5f, -10.0f, 10.f);
    break;
  }
  case eFree:
  {
    mProjection           = glm::perspective(mFOV, mAspectRatio, mNearClip, mFarClip);
    const float3& lSide   = glm::cross( mDirection, mUp );
    quaternion lPitchQuat = glm::angleAxis(mPitch, lSide);
    mUp                   = glm::cross(lSide, mDirection);
    quaternion lYawQuat   = glm::angleAxis(mYaw, mUp);
    glm::quat temp        = glm::cross(lPitchQuat, lYawQuat);
    temp                  = glm::normalize(temp);
    mDirection            = glm::rotate(temp, mDirection);
    mLookAt               = mPosition + mDirection * 1.0f;
    break;
  }
  }
  //compute the MVP
  mView = glm::lookAt(mPosition, mLookAt, mUp);
  float4x4      mProjection;
  float4x4      mView;
  float4x4      mModel;
  float4x4      mMVP;

  mModel = glm::mat4(1.0f);
  mMVP = mProjection * mView * mModel;

  glLoadMatrixf(glm::value_ptr(mMVP));
  ogl::CHECK_OGL_ERROR("finish update camera");
}