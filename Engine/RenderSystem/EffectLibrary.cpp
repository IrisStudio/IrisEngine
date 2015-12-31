#include "EffectLibrary.h"

#include "XML/XML.h"
#include <glm/vec3.hpp>

CEffectLibrary::CEffectLibrary()
{
}

CEffectLibrary::~CEffectLibrary()
{
}

CEffectSPtr CEffectLibrary::CreateEffect(const char* aEffectFile)
{
  CEffectSPtr lEffect;
  xml::CDocument lDocument;
  if (xml::OpenDocument( lDocument, aEffectFile ) )
  {
    xml::CNode lEffectNode = lDocument.child("effect");
    for (xml::CNode lShader = lEffectNode.first_child(); lShader; lShader = lShader.next_sibling() )
    {
      const char* lTag  = lShader.name();
      const char* lFile = lShader.attribute("file").value();
      float3 lVec = xml::GetAttribute<float3>(lShader, "vec3");
      int i = 0;
    }
  }

  return lEffect;
}
