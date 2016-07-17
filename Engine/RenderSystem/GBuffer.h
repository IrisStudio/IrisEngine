#ifndef _GBUFFER_H
#define _GBUFFER_H

#include "Types.h"
#include "Singleton.h"
#include "rs.h"

class CGBuffer : public Singleton< CGBuffer >
{
    public:
        enum ETarget
        {
            eGBT_AlbedoSpec = 0,
            eGBT_WorldSpacePosition,
            eGBT_WorldSpaceNormal,
            eGBT_Count
        };
    public:
        CGBuffer();
        virtual ~CGBuffer();
        void Create(uint32 aWindowWidth, uint32 aWindowHeight);
        void GeometryPass();
        void LightingPass();
        void BindBuffer( ETarget aBufferTarget );
        const uint32* GetRenderTargets() const;
    protected:
    private:
        DISALLOW_COPY_AND_ASSIGN(CGBuffer);
        uint32 mID;
        uint32 mRenderTargets[eGBT_Count];
        uint32 mDepth;
};

#endif