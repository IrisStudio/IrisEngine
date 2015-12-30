#include "XML.h"

#include <glm/vec3.hpp>

namespace xml
{
  template<> glm::vec3 GetAttribute<glm::vec3>(const CNode& aNode, const char* aAttributeName)
  {
    const char* lValue = aNode.attribute(aAttributeName).value();
    glm::vec3 lVec3;
    sscanf_s(lValue, "%f,%f,%f", &lVec3.x, &lVec3.y, &lVec3.z );
    return lVec3;
  }
}