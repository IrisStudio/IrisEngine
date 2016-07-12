#ifndef _GBUFFER_H
#define _GBUFFER_H

#include "Types.h"
#include "Singleton.h"
#include "rs.h"

class CGBuffer : public Singleton< CGBuffer >
{
    public:
        CGBuffer();
        virtual ~CGBuffer();
        void Create();
        void Bind();
    protected:
    private:
        DISALLOW_COPY_AND_ASSIGN(CGBuffer);
        uint32 mID;
        uint32 mRenderTargets[eGBT_Count];
};

#endif