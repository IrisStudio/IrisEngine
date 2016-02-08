#include "Renderer.h"

#include "ogl.h"
#include "VAO.h"
using namespace ogl;

CVao::CVao()
  : mID(0)
{

}

CVao::~CVao()
{
}

void CVao::Create()
{
  glGenVertexArrays(1, &mID);
  glBindVertexArray(mID);
}