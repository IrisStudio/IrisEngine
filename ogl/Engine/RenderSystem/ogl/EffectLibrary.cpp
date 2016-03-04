#include "EffectLibrary.h"

#include "XML/XML.h"
#include "io/io.h"
#include "Shader.h"
#include "Effect.h"
#include "Logger/Logger.h"

#include <string>
#include <fstream>
#include <streambuf>

namespace
{
  typedef std::map< uint32, CShaderSPtr > TMapShader;

  CShaderSPtr CompileAndStoreShader( const uint32 aID, CShader::EType aShaderType, const std::string& aFile, TMapShader& aMap )
  {
	  CShaderSPtr lShader;
	  CShader shader;
	  //iris::io::Serialize(shader);
		 /*

    // First try to find if the shader is already on the map
    TMapShader::const_iterator lFind = aMap.find(aID);
    if (lFind != aMap.end())
      return lFind->second;

    // Is not on the map, then compile it and return it if all
    
    std::ifstream t(aFile);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    lShader = CShaderSPtr(new CShader());
    if (lShader->Create(aShaderType, str.c_str()))
      aMap[aID] = lShader;

    assert(lShader->IsOk());
	*/
    return lShader;
  }
}

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
        lVertexShader = CompileAndStoreShader(str_hash, CShader::VERTEX_SHADER, lFile, mVertexShaderLibrary);
      else if (lTag == "pixel_shader")
        lPixelShader = CompileAndStoreShader(str_hash, CShader::PIXEL_SHADER, lFile, mPixelShaderLibrary);
    }
  }

  if (lVertexShader && lPixelShader)
    lEffect = CEffectSPtr( new CEffect( lVertexShader, lPixelShader ) );

  return lEffect;
}
