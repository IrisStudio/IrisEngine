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
  uint32 GetProgramID() const;
  uint32 GetShaderID() const;
  EType GetType() const;
  bool  IsOk() const;

private: // Members
  uint32       mProgramID, mShaderID;
  EType        mType;
  std::string  mCode;
  bool         mOk;
private: // Methods
  bool Compile();
  bool Link();
};

inline uint32         CShader::GetProgramID() const   { return mProgramID; }
inline uint32         CShader::GetShaderID() const    { return mShaderID; }
inline bool           CShader::IsOk()  const   { return mOk; }
inline CShader::EType CShader::GetType() const { return mType; }

typedef Loki::SmartPtr<CShader> CShaderSPtr;

#endif
