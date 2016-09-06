#ifndef __IO_RESOURCE__
#define __IO_RESOURCE__

#include <string>
#include "ResourceNode.h"

class CResource
{
    public:
        CResource(const std::string& aFilename);

		virtual ~CResource();

        const std::string& GetFilename()           const;
        const std::string& GetFullFilename()       const;
        const std::string& GetFullFilenameSchema() const;
        const std::string& GetDirectory()          const;
        const std::string& GetExtension()          const;
        const std::string& GetHash()               const;

        const std::string GetFileContent() const;

		bool Open();
		CResourceNode GetRoot() const;

    private:
        std::string mFilename;
        std::string mFilenameSchema;
        std::string mFullFilename;
        std::string mFullFilenameSchema;
        std::string mDirectory;
        std::string mExtension;
        std::string mHash;

		tinyxml2::XMLDocument* mDoc;
		tinyxml2::XMLElement* mRootNode;

        void Fill();
};

//---------------------------------------------------------------------------------------------
inline const std::string& CResource::GetFilename() const
{
    return mFilename;
}

//---------------------------------------------------------------------------------------------
inline const std::string& CResource::GetFullFilenameSchema() const
{
    return mFullFilenameSchema;
}

//---------------------------------------------------------------------------------------------
inline const std::string& CResource::GetDirectory() const
{
    return mDirectory;
}

//---------------------------------------------------------------------------------------------
inline const std::string& CResource::GetExtension() const
{
    return mExtension;
}

//---------------------------------------------------------------------------------------------
inline const std::string& CResource::GetHash() const
{
    return mHash;
}

//---------------------------------------------------------------------------------------------
inline const std::string& CResource::GetFullFilename() const
{
    return mFullFilename;
}

#endif // __IO_RESOURCE__
