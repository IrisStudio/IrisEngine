#include "Effect.h"
#include "Shader.h"
#include "ogl.h"
#include "Logger/Logger.h"
#include "Types.h"


CEffect::CEffect(CShaderSPtr aVertexShader, CShaderSPtr aPixelShader)
    : mID(0)
    , mVertexShader(aVertexShader)
    , mFragmentShader(aPixelShader)
{
    ogl::CheckOGLError("Before creating the pipeline");
    ogl::glGenProgramPipelines(1, &mID);
    ogl::glBindProgramPipeline(mID);
    ogl::glUseProgramStages(mID, GL_VERTEX_SHADER_BIT, mVertexShader->GetProgramID() );
    ogl::glUseProgramStages(mID, GL_FRAGMENT_SHADER_BIT, mFragmentShader->GetProgramID());
    ogl::CheckOGLError("After creating the pipeline");
}

CEffect::CEffect(const char* aVertexShader, const char* aPixelShader)
    : mID(0)
    , mVertexShader(new CShader())
    , mFragmentShader(new CShader())
{
    ogl::CheckOGLError("Before creating the pipeline");
    bool lOk = mVertexShader->Create(ShaderType::eST_Vertex, aVertexShader);
    lOk &= mFragmentShader->Create(ShaderType::eST_Fragment, aPixelShader);
    assert(lOk);
    ogl::glGenProgramPipelines(1, &mID);
    ogl::glBindProgramPipeline(mID);
    ogl::glUseProgramStages(mID, GL_VERTEX_SHADER_BIT, mVertexShader->GetProgramID());
    ogl::glUseProgramStages(mID, GL_FRAGMENT_SHADER_BIT, mFragmentShader->GetProgramID());
    ogl::CheckOGLError("After creating the pipeline");
}

CEffect::~CEffect()
{
    ogl::glDeleteProgramPipelines(1, &mID);
}

void CEffect::Bind()
{
    ogl::CheckOGLError("CEffect::Bind() before");
    bool lIsPipeline = ogl::glIsProgramPipeline(mID) == GL_TRUE;
    ogl::glBindProgramPipeline(mID);
    ogl::CheckOGLError("CEffect::Bind() after");
}

void CEffect::BindMatrices(const float4x4& M, const float4x4& V, const float4x4& P)
{
    ogl::CheckOGLError("Before bind matrices");

    const uint32 lVertexShaderID = mVertexShader->GetProgramID();
    GLint modelLoc = ogl::glGetUniformLocation(lVertexShaderID, "model");
    GLint viewLoc = ogl::glGetUniformLocation(lVertexShaderID, "view");
    GLint projLoc = ogl::glGetUniformLocation(lVertexShaderID, "projection");

    ogl::glProgramUniformMatrix4fv(lVertexShaderID, modelLoc, 1, GL_FALSE, &M[0][0]);
    ogl::glProgramUniformMatrix4fv(lVertexShaderID, viewLoc, 1, GL_FALSE, &V[0][0]);
    ogl::glProgramUniformMatrix4fv(lVertexShaderID, projLoc, 1, GL_FALSE, &P[0][0]);

    ogl::CheckOGLError("after bind matrices");
}

// Template implementation
template <>
void CEffect::BindUniform<float4>(const uint32& Id, const int& varLoc, const float4& in)
{
    ogl::CheckOGLError("Before Bind uniform");
    ogl::oglProgramUniform4fv(Id, varLoc, 1, &in[0]);
    ogl::CheckOGLError("After Bind uniform");
}
IMPLEMENT_BIND_UNIFORM(float4)

template <>
void CEffect::BindUniform<float4x4>(const uint32& Id, const int& varLoc, const float4x4& in)
{
    ogl::CheckOGLError("Before Bind uniform");
    ogl::glProgramUniformMatrix4fv(Id, varLoc, 1, GL_FALSE, &in[0][0]);
    ogl::CheckOGLError("After Bind uniform");
}
IMPLEMENT_BIND_UNIFORM(float4x4)