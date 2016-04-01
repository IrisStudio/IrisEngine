
#include "ogl.h"
#include "rs.h"

#include "Geometry.h"

namespace
{
    // Sizes and offsets!
    static const uint32 eGD_PositionSize       = 3 * sizeof(float);
    static const uint32 eGD_ScreenPositionSize = 2 * sizeof(float);
    static const uint32 eGD_NormalSize         = 3 * sizeof(float);
    static const uint32 eGD_TangentSize        = 3 * sizeof(float);
    static const uint32 eGD_BinormalSize       = 3 * sizeof(float);
    static const uint32 eGD_UV                 = 2 * sizeof(float);
    static const uint32 eGD_UV2                = 2 * sizeof(float);

    template < uint32 N > void FillBuffer(void * aVertexBuffer, uint32 aVertexSize );
    template <> void FillBuffer<eGD_Position>( void * aVertexBuffer, uint32 aVertexSize )
    {
        ogl::CheckOGLError("Before creating geometry");
        ogl::glBufferData(GL_ARRAY_BUFFER, aVertexSize * eGD_PositionSize, aVertexBuffer, GL_STATIC_DRAW);
        ogl::glEnableVertexAttribArray(0);
        ogl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        ogl::CheckOGLError("After creating geometry");
    }

    template <> void FillBuffer<eGD_ScreenPosition>( void * aVertexBuffer, uint32 aVertexSize )
    {
        ogl::CheckOGLError("Before creating geometry");
        ogl::glBufferData(GL_ARRAY_BUFFER, aVertexSize * eGD_ScreenPositionSize, aVertexBuffer, GL_STATIC_DRAW);
        ogl::glEnableVertexAttribArray(0);
        ogl::glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        ogl::CheckOGLError("After creating geometry");
    }

    typedef void(*TCreateFunction)(void*, uint32);
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
    , mIB(0)
{
}

CGeometry::~CGeometry()
{
  ogl::CHECK_OGL_ERROR("After deleting the geometry");
  ogl::glDeleteBuffers(1, &mVB);
  ogl::glDeleteBuffers(1, &mIB);
  ogl::glDeleteVertexArrays(1, &mVAO);
  ogl::CHECK_OGL_ERROR("After deleting the geometry");
}

void CGeometry::Create( const uint32 aFlags, void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexCount, uint32 aIndexCount )
{
    mVertexCount = aVertexCount;
    mIndexCount = aIndexCount;

    // Generate the VAO of this geometry
    ogl::glGenVertexArrays(1, &mVAO);
    ogl::glBindVertexArray(mVAO);

    // Create the vertex buffer
    ogl::glGenBuffers(1, &mVB);
    ogl::glBindBuffer(GL_ARRAY_BUFFER, mVB);

    TMapCreateFunctions::iterator lItfind = map2Func.find(aFlags);
    assert(lItfind != map2Func.end());
    
    lItfind->second( aVertexBuffer, mVertexCount);

    ogl::CheckOGLError("Before IB");
    // Create the index buffer
    ogl::glGenBuffers(1, &mIB);
    ogl::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIB);
    ogl::glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * sizeof( uint32 ), aIndexBuffer, GL_STATIC_DRAW);
    ogl::CheckOGLError("After IB");

    ogl::glBindVertexArray(0); // Unbind VAO
}

void CGeometry::Bind() const
{
    ogl::glBindVertexArray(mVAO);
    glEnable(GL_DEPTH_TEST);
    ogl::CheckOGLError("Before draw elements");
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    ogl::CheckOGLError("After draw elements");
}