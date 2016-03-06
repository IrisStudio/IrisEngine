#ifndef __OGL_SHADER__
#define __OGL_SHADER__

#include <Types.h>
#include "rs.h"

class CShader
{
    public:
        CShader();
        virtual ~CShader();
        bool Create( ShaderType aType, const char* aCode);
        uint32 GetProgramID() const;
        uint32 GetShaderID() const;
        ShaderType GetType() const;
        bool  IsOk() const;

    private: // Members
        uint32       mProgramID, mShaderID;
        ShaderType   mType;
        std::string  mCode;
        bool         mOk;
    private: // Methods
        bool Compile();
        bool Link();
};

inline uint32         CShader::GetProgramID() const
{
    return mProgramID;
}

inline uint32         CShader::GetShaderID() const
{
    return mShaderID;
}

inline bool           CShader::IsOk()  const
{
    return mOk;
}

inline ShaderType CShader::GetType() const
{
    return mType;
}

typedef std::shared_ptr<CShader> CShaderSPtr;

#endif
