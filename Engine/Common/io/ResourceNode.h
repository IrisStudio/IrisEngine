#ifndef __IO_RESOURCE_NODE__
#define __IO_RESOURCE_NODE__

#include <string>
#include <vector>
#include "tinyxml2.h"

class CResourceNode
{
    public:
		CResourceNode();
		CResourceNode(tinyxml2::XMLElement* aNode);
		virtual ~CResourceNode();
		template< typename T > T GetAttribute(const char* aAttributeName, const T& aDefault );
		CResourceNode& operator=(tinyxml2::XMLElement* aNode)
		{
			mNode = aNode;
			return *this;
		}
		std::string GetName() const;
		bool IsOk() const;

		size_t GetNumChildren();
		CResourceNode operator[](size_t aIdx) const;
	private:
		tinyxml2::XMLElement* mNode;
		std::vector< tinyxml2::XMLElement* > mChildren;
};

#endif // __IO_RESOURCE__
