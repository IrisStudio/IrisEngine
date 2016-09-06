#include "ResourceNode.h"
#include "Types.h"

CResourceNode::CResourceNode()
	: mNode( nullptr )
{

}

CResourceNode::CResourceNode(tinyxml2::XMLElement* aNode)
	: mNode( aNode )
{
}

CResourceNode::~CResourceNode()
{
}

size_t CResourceNode::GetNumChildren()
{
	for(tinyxml2::XMLElement* pChildren = mNode->FirstChildElement();
		pChildren != nullptr;
		pChildren = pChildren->NextSiblingElement() )
	{
		mChildren.push_back(pChildren);
	}

	return mChildren.size();
}

CResourceNode CResourceNode::operator[](size_t aIdx) const
{
	return CResourceNode(mChildren[aIdx]);
}

bool CResourceNode::IsOk() const
{
	return mNode != nullptr;
}

std::string CResourceNode::GetName() const
{
	return mNode->Name();
}

template<> std::string CResourceNode::GetAttribute<std::string>(const char* aAttributeName, const std::string& aDefault)
{
	const char* pszRet = mNode->Attribute(aAttributeName);
	return (pszRet == nullptr) ? aDefault : pszRet;
}

template<> float CResourceNode::GetAttribute<float>(const char* aAttributeName, const float& aDefault )
{
	float fRet = 0.0f;
	tinyxml2::XMLError eResult = mNode->QueryFloatAttribute(aAttributeName, &fRet);
	return (eResult != tinyxml2::XML_SUCCESS) ? aDefault : fRet;
}

template<> float3 CResourceNode::GetAttribute<float3>(const char* aAttributeName, const float3& aDefault )
{
	float3 lVec3(aDefault);
	std::string lValue = GetAttribute< std::string >( aAttributeName, "" );
	if(!lValue.empty())
		sscanf_s(lValue.c_str(), "%f %f %f", &lVec3.x, &lVec3.y, &lVec3.z);
	return lVec3;
}

template<> float4 CResourceNode::GetAttribute<float4>(const char* aAttributeName, const float4& aDefault )
{
	float4 lVec4(aDefault);
	std::string lValue = GetAttribute< std::string >(aAttributeName, "");
	if (!lValue.empty())
		sscanf_s(lValue.c_str(), "%f %f %f %f", &lVec4.x, &lVec4.y, &lVec4.z, &lVec4.w);
	return lVec4;
}

template<> bool CResourceNode::GetAttribute<bool>(const char* aAttributeName, const bool& aDefault )
{
	bool bRet = false;
	tinyxml2::XMLError eResult = mNode->QueryBoolAttribute(aAttributeName, &bRet);
	return (eResult != tinyxml2::XML_SUCCESS) ? aDefault : bRet;
}