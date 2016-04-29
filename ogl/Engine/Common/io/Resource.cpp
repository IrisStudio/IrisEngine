#include "Resource.h"

#include <fstream>
#include <streambuf>

//---------------------------------------------------------------------------------------------
CResource::CResource(const std::string& aFilename)
    : mFilename(aFilename)
{
    Fill();
}

//---------------------------------------------------------------------------------------------
CResource::CResource(const std::string& aFilename, const std::string& aFileNameSchema)
    : mFilename(aFilename)
    , mFilenameSchema(aFileNameSchema)
{
    Fill();
}

//---------------------------------------------------------------------------------------------
void CResource::Fill()
{
    mFullFilename           = "../data/" + mFilename;

    if( !mFilenameSchema.empty() )
    {
        mFullFilenameSchema     = "../data/" + mFilenameSchema;
    }

    size_t found = mFullFilename.find_last_of("/\\");
    mDirectory = (mFullFilename.substr(0, found)) + "/";
}

//---------------------------------------------------------------------------------------------
const std::string CResource::GetFileContent() const
{
    std::ifstream t(mFullFilename);
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}