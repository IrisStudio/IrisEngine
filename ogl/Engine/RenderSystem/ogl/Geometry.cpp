
#include "ogl.h"
#include "rs.h"

#include "Geometry.h"

CGeometry::CGeometry()
    : mVao(0)
    , mVB(0)
{

}

CGeometry::~CGeometry()
{
}

void CGeometry::Create(uint32 aFlags, void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize)
{
    // Generate the VAO of this geometry
    ogl::glGenVertexArrays(1, &mVao);
    ogl::glBindVertexArray(mVao);

    //
    ogl::glGenBuffers(1, &mVB);
    ogl::glBindBuffer(GL_ARRAY_BUFFER, mVB);
    //FillBufferData< aFlags >(aVertexBuffer, aVertexSize );
}

void CGeometry::Bind() const
{
    ogl::glBindVertexArray(mVao);
}


template<>
void CGeometry::FillBufferData< eGD_ScreenPosition >(void* aVertexBuffer, uint32 aVertexCount)
{
    ogl::glBufferData(GL_ARRAY_BUFFER, aVertexCount * sizeof(float), aVertexBuffer, GL_STATIC_DRAW);
}

template<>
void CGeometry::FillBufferData< eGD_ScreenPosition | eGD_Normal >(void* aVertexBuffer, uint32 aVertexCount)
{
    ogl::glBufferData(GL_ARRAY_BUFFER, aVertexCount * sizeof(float), aVertexBuffer, GL_STATIC_DRAW);
}