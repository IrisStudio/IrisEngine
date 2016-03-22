#include "BoxMesh.h"

CBoxMesh::CBoxMesh()
  : CMesh()
{
  float length  = 1.0f;
  float width   = 1.0f;
  float height  = 1.0f;

  float3 p0(-length * .5f, -width * .5f, height * .5f);
  float3 p1(length * .5f, -width * .5f, height * .5f);
  float3 p2(length * .5f, -width * .5f, -height * .5f);
  float3 p3(-length * .5f, -width * .5f, -height * .5f);

  float3 p4(-length * .5f, width * .5f, height * .5f);
  float3 p5(length * .5f, width * .5f, height * .5f);
  float3 p6(length * .5f, width * .5f, -height * .5f);
  float3 p7(-length * .5f, width * .5f, -height * .5f);

  mVtx = new float3[ 6 * 4 ]
  {
    // Bottom
    p0, p1, p2, p3,

    // Left
    p7, p4, p0, p3,

    // Front
    p4, p5, p1, p0,

    // Back
    p6, p7, p3, p2,

    // Right
    p5, p6, p2, p1,

    // Top
    p7, p6, p5, p4
  };
}


CBoxMesh::~CBoxMesh()
{
}