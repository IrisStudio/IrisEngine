#pragma once
#ifndef _CFullScreenQuad_
#define _CFullScreenQuad_

#include "Types.h"
#include "Mesh.h"

class CFullScreenQuad : public CMesh
{
    public:
        CFullScreenQuad();
        virtual ~CFullScreenQuad();

        void Init(float aLenght, float aWidht, float aHeight);

    protected:

    private:
        DISALLOW_COPY_AND_ASSIGN(CFullScreenQuad);
};

typedef std::shared_ptr< CFullScreenQuad > CFullScreenQuadSPtr;

#endif