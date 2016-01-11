#include "Effect.h"
#include "Shader.h"
#include "ogl.h"
#include "Logger/Logger.h"

CEffect::CEffect(CShaderSPtr aVertexShader, CShaderSPtr aPixelShader)
  : mID(0)
{
  //glGenProgramPipelines(1, &mID);
  //glBindProgramPipeline(mID);
  //glUseProgramStages(mID, GL_VERTEX_SHADER_BIT, aVertexShader->GetID());
  //glUseProgramStages(mID, GL_FRAGMENT_SHADER_BIT, aPixelShader->GetID());
  IRIS_LOG_ERROR_IF(glGetError() != GL_NO_ERROR, "PIPELINE_ERRORS");
}

CEffect::~CEffect()
{

}
