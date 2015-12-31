#ifndef __XML__
#define __XML__

#include "pugixml/pugixml.hpp"

namespace xml
{
  typedef pugi::xml_document      CDocument;
  typedef pugi::xml_node          CNode;

  bool OpenDocument(CDocument& aDocument, const char* aFileName);
  template< typename T > T GetAttribute( const CNode& aNode, const char* aAttributeName );
}

#endif
