
#pragma once
#ifndef _CCamera_
#define _CCamera_

#include "Types.h"

namespace gph
{
  enum ECameraType
  {
    eFree = 0,
    eFPS,
    eTPS,
    eOrtho,
  };
  class CCamera
  {
  public:
    CCamera();
    CCamera( ECameraType aType );
    virtual ~CCamera();
  private:
    void          SetPosition( const float3& aPosition );
    const float3& GetPosition( ) const;

    void          SetLookAt( const float3& aLookAt );
    const float3& GetLookAt( ) const;

    void          SetFOV     ( float aFOV );
    float         GetFOV     ( ) const;

    void          SetClipPlanes( float aFar, float aNear);
    float         GetClipPlanes( float& aFar, float& aNear) const;

    void          SetViewport(uint32 aPosX, uint32 aPosY, uint32 aWidth, uint32 aHeight );
    void          GetViewport (uint32 &aPosX, uint32 &aPosY, uint32 &aWidth, uint32 &aHeight );

    void          GetMatricies(float4x4 &P, float4x4 &V, float4x4 &M) const;

    void          ChangeYaw   ( float aDeg );
    void          ChangePitch ( float aDeg );

  private:
    DISALLOW_COPY_AND_ASSIGN(CCamera);

    float3        mPosition;
    float3        mLookAt;
    float3        mUp;
    float3        mDirection;
    float3        mDelta;
    quaternion    mRotation;

    float         mAspectRatio;
    float         mFOV;
    float         mNearClip;
    float         mFarClip;

    uint32        mViewportX;
    uint32        mViewportY;
    uint32        mViewportWidth;
    uint32        mViewportHeight;

    float4x4      mProjection;
    float4x4      mView;
    float4x4      mModel;
    float4x4      mMVP;
  };
}

typedef Loki::SmartPtr< gph::CCamera > CCameraSPtr;

#endif