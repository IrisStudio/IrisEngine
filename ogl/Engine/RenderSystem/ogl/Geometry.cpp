
#include "ogl.h"
#include "rs.h"

#include "Geometry.h"

namespace
{
    template < uint32 N > void FillBuffer(const uint32 aVB, void * aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize);
    template <> void FillBuffer<eGD_Position>(const uint32 aVB, void * aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize)
    {
        printf("eGD_Position");
        ogl::CheckOGLError("Before creating geometry");
        ogl::glBufferData(GL_ARRAY_BUFFER, aVertexSize * sizeof(float), aVertexBuffer, GL_STATIC_DRAW);
        ogl::glEnableVertexAttribArray(0);
        ogl::glBindBuffer(GL_ARRAY_BUFFER, aVB);
        ogl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        ogl::CheckOGLError("After creating geometry");
    }

    template <> void FillBuffer<eGD_ScreenPosition>( const uint32 aVB, void * aVertexBuffer, void* aIndexBuffer, uint32 aVertexSize, uint32 aIndexSize)
    {
        printf("eGD_ScreenPosition");
        ogl::CheckOGLError("Before creating geometry");
        ogl::glBufferData(GL_ARRAY_BUFFER, aVertexSize * sizeof(float), aVertexBuffer, GL_STATIC_DRAW);
        ogl::glEnableVertexAttribArray(0);
        ogl::glBindBuffer(GL_ARRAY_BUFFER, aVB);
        ogl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        ogl::CheckOGLError("After creating geometry");
    }

    typedef void(*TCreateFunction)(const uint32, void*, void*, uint32, uint32);
    typedef std::map<uint32, TCreateFunction> TMapCreateFunctions;
#define REGISTER_FILLBUFFER_FNC( enum ) { enum, FillBuffer<enum> }
    TMapCreateFunctions map2Func =
    {
        REGISTER_FILLBUFFER_FNC(eGD_Position),
        REGISTER_FILLBUFFER_FNC(eGD_ScreenPosition),
    };
#undef REGISTER_FILLBUFFER_FNC
}

CGeometry::CGeometry()
    : mVAO(0)
    , mVB(0)
{
}

CGeometry::~CGeometry()
{
}

void CGeometry::Create( const uint32 aFlags, void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexCount, uint32 aIndexCount )
{
    // Generate the VAO of this geometry
    ogl::glGenVertexArrays(1, &mVAO);
    ogl::glBindVertexArray(mVAO);

    // Create the vertex buffer
    ogl::glGenBuffers(1, &mVB);
    ogl::glBindBuffer(GL_ARRAY_BUFFER, mVB);

    TMapCreateFunctions::iterator lItfind = map2Func.find(aFlags);

    if( lItfind != map2Func.end() )
    {
        lItfind->second( mVB, aVertexBuffer, aIndexBuffer, aVertexCount, aIndexCount);
    }

    ogl::glBindVertexArray(0); // Unbind VAO
}

void CGeometry::Bind() const
{
    ogl::glBindVertexArray(mVAO);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
}