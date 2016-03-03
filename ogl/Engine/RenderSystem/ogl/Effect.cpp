#include "Effect.h"
#include "Shader.h"
#include "ogl.h"
#include "Logger/Logger.h"

using namespace ogl;

CEffect::CEffect(CShaderSPtr aVertexShader, CShaderSPtr aPixelShader)
  : mID(0)
{
  glGenProgramPipelines(1, &mID);
  CHECK_OGL_ERROR("Creating pipeline %d", mID);
  glBindProgramPipeline(mID);
  CHECK_OGL_ERROR("Creating pipeline %d", mID);
  glUseProgramStages(mID, GL_VERTEX_SHADER_BIT, aVertexShader->GetProgramID() );
  CHECK_OGL_ERROR("Creating pipeline %d", mID);
  glUseProgramStages(mID, GL_FRAGMENT_SHADER_BIT, aPixelShader->GetProgramID());
  CHECK_OGL_ERROR("Creating pipeline %d", mID);
}

CEffect::~CEffect()
{

}

void CEffect::Bind()
{
  glBindProgramPipeline(mID);
}
