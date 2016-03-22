#include "Mesh.h"

CMesh::CMesh()
{
}


CMesh::~CMesh()
{
  free(mVtx);
}