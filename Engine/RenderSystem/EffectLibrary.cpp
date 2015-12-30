#include "EffectLibrary.h"

#include "XML/pugixml.hpp"

CEffectLibrary::CEffectLibrary()
{
}

CEffectLibrary::~CEffectLibrary()
{
}

CEffectSPtr CEffectLibrary::CreateEffect(const char* aEffectFile)
{
  CEffectSPtr lEffect;
  pugi::xml_document lDocument;
  if (lDocument.load_file(aEffectFile))
  {
    pugi::xml_node lEffectNode = lDocument.child("effect");
    for (pugi::xml_node lShader = lEffectNode.first_child(); lShader; lShader = lShader.next_sibling() )
    {
      const char* lTag  = lShader.name();
      const char* lFile = lShader.attribute("file").value();
    }
  }

  return lEffect;
}
