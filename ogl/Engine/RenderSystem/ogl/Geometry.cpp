
#include "ogl.h"
#include "rs.h"

#include "Geometry.h"

CGeometry::CGeometry()
    : mVao(0)
    , mVB(0)
{
    // Generate the VAO of this geometry
    ogl::glGenVertexArrays(1, &mVao);
    ogl::glBindVertexArray(mVao);

    //
    ogl::glGenBuffers(1, &mVB);
    ogl::glBindBuffer(GL_ARRAY_BUFFER, mVB);
}

CGeometry::~CGeometry()
{
}

template <>
void CGeometry::Create<eGD_ScreenPosition>( void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize)
{
    printf("eGD_ScreenPosition");
    ogl::CheckOGLError("Before creating geometry");
    ogl::glBufferData(GL_ARRAY_BUFFER, aVertexSize * sizeof(float), aVertexBuffer, GL_STATIC_DRAW);
    ogl::glEnableVertexAttribArray(0);
    ogl::glBindBuffer(GL_ARRAY_BUFFER, mVB);
    ogl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    ogl::CheckOGLError("After creating geometry");
}

template <>
void CGeometry::Create<eGD_Position>(void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize)
{
    printf("eGD_Position");
}

template <>
void CGeometry::Create< eGD_Position | eGD_Normal >(void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize)
{
    printf("eGD_Position | eGD_Normal");
}

void CGeometry::Bind() const
{
    ogl::glBindVertexArray(mVao);
}