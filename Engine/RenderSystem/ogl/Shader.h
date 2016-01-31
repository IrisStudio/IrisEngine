#ifndef __OGL_SHADER__
#define __OGL_SHADER__

#include <Types.h>
#include <loki/SmartPtr.h>

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
  EType GetType() const;
  bool  IsOk() const;

private:
  uint32 mID;
  EType  mType;
  bool   mOk;
};

inline uint32         CShader::GetID() const { return mID; }
inline bool           CShader::IsOk() const { return mOk; }
inline CShader::EType CShader::GetType() const { return mType; }

typedef Loki::SmartPtr<CShader> CShaderSPtr;

#endif
