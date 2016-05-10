#include "Mesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
}

void CMesh::Render( uint32 aIdx )
{
	assert(mGeometry.size() > aIdx && aIdx >= 0);
	mGeometry[aIdx]->Bind();
}

void CMesh::Clear()
{
	mGeometry.clear();
}

uint32 CMesh::GetGeometryCount() const
{
	return mGeometry.size();
}

void CMesh::AddGeometry(CGeometrySPtr aGeometry)
{
	mGeometry.push_back(aGeometry);
}

CGeometrySPtr CMesh::GetGeometry(uint32 aIdx) const
{
    assert(mGeometry.size() > aIdx && aIdx > -1);
	return mGeometry[aIdx];
}
