#include "Cube.h"

CCube::CCube()
  : CMesh()
{
}


CCube::~CCube()
{
}

void CCube::Init( float aLenght, float aWidht, float aHeight )
{
  float3 p0(-aLenght * .5f, -aWidht * .5f, aHeight * .5f);
  float3 p1(aLenght * .5f, -aWidht * .5f, aHeight * .5f);
  float3 p2(aLenght * .5f, -aWidht * .5f, -aHeight * .5f);
  float3 p3(-aLenght * .5f, -aWidht * .5f, -aHeight * .5f);

  float3 p4(-aLenght * .5f, aWidht * .5f, aHeight * .5f);
  float3 p5(aLenght * .5f, aWidht * .5f, aHeight * .5f);
  float3 p6(aLenght * .5f, aWidht * .5f, -aHeight * .5f);
  float3 p7(-aLenght * .5f, aWidht * .5f, -aHeight * .5f);

  float3*vertices = new float3[6*4]
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

  mGeometry->Create(eGD_Position, vertices, nullptr, 6 * 4, 0);
}