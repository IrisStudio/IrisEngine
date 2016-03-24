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
    ogl::glGenProgramPipelines(1, &mID);
    ogl::CHECK_OGL_ERROR("Creating pipeline %d", mID);
    ogl::glBindProgramPipeline(mID);
    ogl::CHECK_OGL_ERROR("Creating pipeline %d", mID);
    ogl::glUseProgramStages(mID, GL_VERTEX_SHADER_BIT, aVertexShader->GetProgramID() );
    ogl::CHECK_OGL_ERROR("Creating pipeline %d", mID);
    ogl::glUseProgramStages(mID, GL_FRAGMENT_SHADER_BIT, aPixelShader->GetProgramID());
    ogl::CHECK_OGL_ERROR("Creating pipeline %d", mID);
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
    ogl::CHECK_OGL_ERROR("after bind matrices");

    ogl::glProgramUniformMatrix4fv(mVertexShader->GetProgramID(), modelLoc, 1, GL_FALSE, &M[0][0]);
    ogl::glProgramUniformMatrix4fv(mVertexShader->GetProgramID(), viewLoc, 1, GL_FALSE, &V[0][0]);
    ogl::glProgramUniformMatrix4fv(mVertexShader->GetProgramID(), projLoc, 1, GL_FALSE, &P[0][0]);


    ogl::CHECK_OGL_ERROR("after bind matrices");
}
