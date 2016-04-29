#pragma once
#ifndef _CMesh_
#define _CMesh_

#include "Types.h"
#include "gph.h"
#include "Geometry.h"
#include "Texture.h"

class CEffect;

class CMesh
{
    public:
        CMesh();
        virtual ~CMesh();
        void Render();

        void          SetColor(const float4& color);
        const float4& GetColor() const;

		void		  SetGeometry( CGeometrySPtr aGeometry);

    protected:
        CGeometrySPtr mGeometry;
        CEffect*      mEffect;
        CTexture      mTex;

        float4 mColor;

    private:
        DISALLOW_COPY_AND_ASSIGN(CMesh);
};

typedef std::shared_ptr< CMesh > CMeshSPtr;

#endif