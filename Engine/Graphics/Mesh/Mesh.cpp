#include "Mesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
}

void CMesh::Resize(uint32 aSize)
{
    mGeometries.resize(aSize);
}

void CMesh::Render( uint32 aIdx )
{
    assert(mGeometries.size() > aIdx && aIdx >= 0);

    for each ( CGeometrySPtr lGeometry in mGeometries[ aIdx ] )
    {
        lGeometry->Bind();
    }
}

void CMesh::Clear()
{
    mGeometries.clear();
}

uint32 CMesh::GetGeometryCount() const
{
    return mGeometries.size();
}

void CMesh::AddGeometry(uint32 aMaterialId, CGeometrySPtr aGeometry)
{
    mGeometries[aMaterialId].push_back(aGeometry);
}

CGeometrySPtr CMesh::GetGeometry(uint32 aIdx) const
{
    assert(mGeometries.size() > aIdx && aIdx > -1);
    return mGeometries[aIdx].front();
}
