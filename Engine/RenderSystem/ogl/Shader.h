#ifndef __OGL_SHADER__
#define __OGL_SHADER__

#include <Types.h>

namespace renderer
{
  class CShader
  {
  public:

    enum EType
    {
      VERTEX_SHADER = 0x8B31,
      PIXEL_SHADER  = 0x8B30,
    };

  public:
    CShader();
    virtual ~CShader();
    bool Create( EType aType, const char* aCode );
    uint32 GetID() const;

  private:
    uint32 mID;
  };

  inline uint32 CShader::GetID() const { return mID;  }
}

#endif
