
#pragma once
#ifndef _CCamera_
#define _CCamera_

#include "Types.h"

enum ECameraType
{
    eFree = 0,
    eFPS,
    eTPS,
    eOrtho,
};

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class CCamera
{
    public:
        CCamera();
        virtual ~CCamera();
        void     Update();

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void          SetPosition( const float3& aPosition );
        const float3& GetPosition( ) const;

        void          SetLookAt( const float3& aLookAt );
        const float3& GetLookAt( ) const;

        const float3& GetDirection() const;

        void          SetFOV     ( float aFOV );
        float         GetFOV     ( ) const;

        void          SetClipPlanes( float aFar, float aNear);
        void          GetClipPlanes( float& aFar, float& aNear) const;

        void          SetViewport(uint32 aPosX, uint32 aPosY, uint32 aWidth, uint32 aHeight );
        void          GetViewport (uint32 &aPosX, uint32 &aPosY, uint32 &aWidth, uint32 &aHeight );

        void          GetMatrices(float4x4 &P, float4x4 &V, float4x4 &M) const;

        void          ChangeYaw   ( float aDeg );
        void          ChangePitch ( float aDeg );

    private:
        DISALLOW_COPY_AND_ASSIGN(CCamera);

        ECameraType   mType;
        float3        mPosition;
        float3        mLookAt;
        float3        mDirection;
        float3        mUp;
        float3        mDelta;
        float3        mSide;
        quaternion    mRotation;

        float         mAspectRatio;
        float         mFOV;
        float         mNearClip;
        float         mFarClip;
        float         mYaw;
        float         mPitch;

        uint32        mViewportX;
        uint32        mViewportY;
        uint32        mViewportWidth;
        uint32        mViewportHeight;

        bool          mMove;

        float4x4      mProjection;
        float4x4      mView;
        float4x4      mModel;
        float4x4      mMVP;
};

typedef std::shared_ptr< CCamera > CCameraSPtr;

#endif