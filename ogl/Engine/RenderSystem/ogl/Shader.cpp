#include "ogl.h"
#include "Context.h"
#include "Shader.h"
#include "Logger/Logger.h"

std::string CShader::mGLSLVersion = "";

static const char* sAdditionalVertexCode =
    "#extension GL_ARB_separate_shader_objects : enable\n\n"
    "out gl_PerVertex\n"
    "{\n"
    "    vec4 gl_Position;\n"
    "};\n\n";

static const char* sAdditionalFragmentCode =
    "#extension GL_ARB_separate_shader_objects : enable\n\n";

void CShader::SetGLSLVersion(const std::string& aVersion)
{
    mGLSLVersion = "#version " + std::string(aVersion) + " core\n";
}

using namespace ogl;

CShader::CShader()
    : mProgramID(0)
    , mShaderID(0)
    , mType( eST_Vertex )
    , mOk(false)
{
}

CShader::~CShader()
{
    glDeleteShader(mShaderID);
    glDeleteProgram(mProgramID);
}

bool CShader::Create(ShaderType aType, const char * aCode)
{
    mCode = mGLSLVersion + (( aType == eST_Vertex ) ? sAdditionalVertexCode : sAdditionalFragmentCode) + aCode;

    mType = aType;
    mOk = (Compile() && Link());
    return mOk;
}

bool CShader::Compile()
{
    GLint lSuccess = 0;
    mShaderID = glCreateShader(mType);

    if (mShaderID)
    {
        GLint lSizeCode = mCode.length();
        const GLchar* lShaderSrc = mCode.c_str();
        glShaderSource(mShaderID, 1, &lShaderSrc, &lSizeCode);
        glCompileShader(mShaderID);

        glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &lSuccess);

        #ifdef _DEBUG

        if (!lSuccess)
        {
            char lInfoLog[512];
            glGetShaderInfoLog(mShaderID, 512, NULL, lInfoLog);
            LOG_ERROR("Error compiling the shader");
            LOG_ERROR(lInfoLog);
        }

        #endif

    }

    return lSuccess != GL_FALSE;
}

bool CShader::Link()
{
    GLint lSuccess = GL_FALSE;

    mProgramID = glCreateProgram();

    if (mProgramID)
    {
        glProgramParameteri(mProgramID, GL_PROGRAM_SEPARABLE, GL_TRUE);
        glAttachShader(mProgramID, mShaderID);
        glLinkProgram(mProgramID);

        glGetProgramiv(mProgramID, GL_LINK_STATUS, &lSuccess);

        #ifdef _DEBUG

        if (!lSuccess)
        {
            char lInfoLog[512];
            glGetProgramInfoLog(mProgramID, 512, NULL, lInfoLog);
            LOG_ERROR("Error linking the program");
            LOG_ERROR(lInfoLog);
        }

        #endif

        glDetachShader(mProgramID, mShaderID);
    }

    return lSuccess != GL_FALSE;
}
