#include "EffectLibrary.h"

#include "XML/XML.h"
#include "Shader.h"
#include "Effect.h"
#include "RenderSystem.h"
#include "Logger/Logger.h"

#include <string>
#include <fstream>
#include <streambuf>

CEffectLibrary::CEffectLibrary()
{
}

CEffectLibrary::~CEffectLibrary()
{
}

CEffectSPtr CEffectLibrary::CreateEffect(const char* aEffectFile)
{
  CEffectSPtr lEffect;
  CShaderSPtr lVertexShader;
  CShaderSPtr lPixelShader;
  xml::CDocument lDocument;
  if (xml::OpenDocument(lDocument, aEffectFile))
  {
    std::hash<std::string> hash_fn;
    xml::CNode lEffectNode = lDocument.child("effect");
    for (xml::CNode lShaderNode = lEffectNode.first_child(); lShaderNode; lShaderNode = lShaderNode.next_sibling())
    {
      const std::string& lTag  = lShaderNode.name();
      const std::string& lFile = xml::GetAttribute<std::string>(lShaderNode, "file");
      uint32 str_hash = hash_fn(lFile);
      if (lTag == "vertex_shader")
      {
        TMapShader::const_iterator lFind = mVertexShaderLibrary.find(str_hash);
        if (lFind != mVertexShaderLibrary.end())
        {
          lVertexShader = lFind->second;
        }
        else
        {
          std::ifstream t(lFile);
          std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
          lVertexShader = CShaderSPtr(new CShader());
          if (!lVertexShader->Create(CShader::VERTEX_SHADER, str.c_str()))
          {
            IRIS_LOG_ERROR("Error creating vertex shader");
            lVertexShader.reset();
          }
          else
          {
            mVertexShaderLibrary[ str_hash ] = lVertexShader;
          }
        }
      }
      else if (lTag == "pixel_shader")
      {
        TMapShader::const_iterator lFind = mPixelShaderLibrary.find(str_hash);
        if (lFind != mPixelShaderLibrary.end())
        {
          lPixelShader = lFind->second;
        }
        else
        {
          std::ifstream t(lFile);
          std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
          lPixelShader = CShaderSPtr(new CShader());
          if (!lPixelShader->Create(CShader::PIXEL_SHADER, str.c_str()))
          {
            IRIS_LOG_ERROR("Error creating vertex shader");
            lPixelShader.reset();
          }
          else
          {
            mPixelShaderLibrary[str_hash] = lPixelShader;
          }
        }
      }
    }
  }

  if (lVertexShader && lPixelShader)
  {
   lEffect = CEffectSPtr( new CEffect( lVertexShader, lPixelShader ) );
  }

  return lEffect;
}
