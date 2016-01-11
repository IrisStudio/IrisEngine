#include "XML.h"

#include "Types.h"
#include "Logger/Logger.h"
#include <Windows.h>

namespace xml
{
  bool OpenDocument( CDocument& aDocument, const char* aFileName)
  {
    pugi::xml_parse_result lResult = aDocument.load_file(aFileName);
    IRIS_LOG_ERROR_IF(!lResult, lResult.description() );
    return lResult != NULL;
  }

  template<> std::string GetAttribute<std::string>(const CNode& aNode, const char* aAttributeName)
  {
    return aNode.attribute(aAttributeName).value();
  }

  template<> float GetAttribute<float>(const CNode& aNode, const char* aAttributeName)
  {
    const char* lValue = aNode.attribute(aAttributeName).value();
    float lFloat(0.0f);
    sscanf_s(lValue, "%f", &lFloat );
    return lFloat;
  }

  template<> float3 GetAttribute<float3>(const CNode& aNode, const char* aAttributeName)
  {
    const char* lValue = aNode.attribute(aAttributeName).value();
    float3 lVec3(0.0f, 0.0f, 0.0f);
    sscanf_s(lValue, "%f,%f,%f", &lVec3.x, &lVec3.y, &lVec3.z );
    return lVec3;
  }
  
  template<> float4 GetAttribute<float4>(const CNode& aNode, const char* aAttributeName)
  {
    const char* lValue = aNode.attribute(aAttributeName).value();
    float4 lVec4(0.0f, 0.0f, 0.0f, 0.0f);
    sscanf_s(lValue, "%f,%f,%f,%f", &lVec4.x, &lVec4.y, &lVec4.z, &lVec4.w );
    return lVec4;
  }

  template<> bool GetAttribute<bool>(const CNode& aNode, const char* aAttributeName)
  {
    const char* lValue = aNode.attribute(aAttributeName).value();
    return ( strcmp("TRUE", lValue) == 0 || strcmp("true", lValue) == 0 || strcmp("True", lValue) == 0);
  }
}