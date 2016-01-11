#ifndef __OGL_SHADER__
#define __OGL_SHADER__

#include <Types.h>

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

private:
  uint32 mID;
  EType  mType;
};

inline uint32 CShader::GetID() const { return mID; }
inline CShader::EType CShader::GetType() const { return mType; }

#endif
