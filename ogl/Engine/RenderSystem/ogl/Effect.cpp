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
    ogl::CHECK_OGL_ERROR("Before creating the pipeline");
    ogl::glGenProgramPipelines(1, &mID);
    ogl::glBindProgramPipeline(mID);
    ogl::glUseProgramStages(mID, GL_VERTEX_SHADER_BIT, aVertexShader->GetProgramID() );
    ogl::glUseProgramStages(mID, GL_FRAGMENT_SHADER_BIT, aPixelShader->GetProgramID());
    ogl::CHECK_OGL_ERROR("After creating the pipeline");
}

CEffect::~CEffect()
{

}

void CEffect::Bind()
{
    ogl::glBindProgramPipeline(mID);
}

void CEffect::BindMatrices(const float4x4& M, const float4x4& V, const float4x4& P)
{
    ogl::CHECK_OGL_ERROR("Before bind matrices");
    GLint modelLoc = ogl::glGetUniformLocation(mVertexShader->GetProgramID(), "model");
    GLint viewLoc = ogl::glGetUniformLocation(mVertexShader->GetProgramID(), "view");
    GLint projLoc = ogl::glGetUniformLocation(mVertexShader->GetProgramID(), "projection");

    const uint32 lVertexShaderID = mVertexShader->GetProgramID();
    ogl::glProgramUniformMatrix4fv(lVertexShaderID, modelLoc, 1, GL_FALSE, &M[0][0]);
    ogl::glProgramUniformMatrix4fv(lVertexShaderID, viewLoc, 1, GL_FALSE, &V[0][0]);
    ogl::glProgramUniformMatrix4fv(lVertexShaderID, projLoc, 1, GL_FALSE, &P[0][0]);

    GLint colorLoc = ogl::glGetUniformLocation(mFragmentShader->GetProgramID(), "in_color");

    const uint32 lFragmentShaderID = mFragmentShader->GetProgramID();
    const float4 color(0.6f, 0.2f, 0.8f, 1.0f);
    ogl::oglProgramUniform4fv(lFragmentShaderID, colorLoc, 1, &color[0] );

    ogl::CHECK_OGL_ERROR("after bind matrices");
}
