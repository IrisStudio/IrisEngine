#include "Grid.h"

CGrid::CGrid()
  : CMesh()
{
}


CGrid::~CGrid()
{
}

void CGrid::Init(uint32 aRows, uint32 aCols, float aGap)
{
  float points[] =
  {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f,
  };

  if (aRows > 0 && aCols > 0)
  {
    float lFirstX = -(aRows*0.5) * aGap;
    float lFirstZ = -(aCols*0.5) * aGap;
    float* points = (float*)malloc(sizeof(float)* aRows* aCols);
    for (uint32 lCount = 0; lCount < aRows; ++lCount )
    {

    }
  }
}