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
  if (lDocument.load_file(aEffectFile))
  {
    xml::CNode lEffectNode = lDocument.child("effect");
    for (xml::CNode lShader = lEffectNode.first_child(); lShader; lShader = lShader.next_sibling() )
    {
      const char* lTag  = lShader.name();
      const char* lFile = lShader.attribute("file").value();
      glm::vec3 lVec = xml::GetAttribute<glm::vec3>(lShader, "vec3");
    }
  }

  return lEffect;
}
