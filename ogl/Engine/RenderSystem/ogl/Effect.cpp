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
  GLint modelLoc = ogl::glGetUniformLocation(mID, "model");
  GLint viewLoc = ogl::glGetUniformLocation(mID, "view");
  GLint projLoc = ogl::glGetUniformLocation(mID, "projection");

  // Pass the matrices to the shader
  ogl::glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(V));
  ogl::glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(P));
  ogl::glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(M));
  ogl::CHECK_OGL_ERROR("after bind matrices");
}
