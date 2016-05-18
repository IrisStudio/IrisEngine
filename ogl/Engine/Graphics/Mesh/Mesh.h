#pragma once
#ifndef _CMesh_
#define _CMesh_

#include "Types.h"
#include "gph.h"
#include "Geometry.h"

class CEffect;

class CMesh
{
    public:
        CMesh();
        virtual         ~CMesh();

        void            Resize( uint32 aSize );
        void            Render( uint32 aIdx );
        void            Clear();
        uint32          GetGeometryCount() const;
        void            AddGeometry(uint32 aMaterialId, CGeometrySPtr aGeometry);
        CGeometrySPtr   GetGeometry(uint32 aIdx) const;

    protected:
        typedef std::vector< CGeometrySPtr > TGeometryVector;
        typedef std::vector< TGeometryVector > TMaterialGeometries;
        TMaterialGeometries mGeometries;

    private:
        DISALLOW_COPY_AND_ASSIGN(CMesh);
};

typedef std::shared_ptr< CMesh > CMeshSPtr;

#endif