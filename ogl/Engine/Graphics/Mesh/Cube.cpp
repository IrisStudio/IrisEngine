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
    float vertices[] =
    {
      // front
      -1.0, -1.0,  1.0,
      1.0, -1.0,  1.0,
      1.0,  1.0,  1.0,
      -1.0,  1.0,  1.0,
      // back
      -1.0, -1.0, -1.0,
      1.0, -1.0, -1.0,
      1.0,  1.0, -1.0,
      -1.0,  1.0, -1.0,
    };

    uint32 indices[] =
    {
      // front
      0, 1, 2,
      2, 3, 0,
      // top
      1, 5, 6,
      6, 2, 1,
      // back
      7, 6, 5,
      5, 4, 7,
      // bottom
      4, 0, 3,
      3, 7, 4,
      // left
      4, 5, 1,
      1, 0, 4,
      // right
      3, 2, 6,
      6, 7, 3,
    };

    mGeometry->Create(eGD_Position, &vertices, &indices, 24, 36 );
}