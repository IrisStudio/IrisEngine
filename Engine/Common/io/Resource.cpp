#include "Resource.h"

#include "Types.h"
#include <fstream>
#include <streambuf>
#include "MD5.h"
#include "StringUtils.h"
#include "Logger\Logger.h"

CResource::CResource(const std::string& aFilename)
    : mFilename(aFilename)
	, mDoc(nullptr)
	, mRootNode(nullptr)
{
    Fill();
}

CResource::~CResource()
{
	CheckedDelete(mDoc);
}

void CResource::Fill()
{
    if(mFilename.find("../data/") == std::string::npos )
    {
        mFullFilename           = "../data/" + mFilename;
    }
    else
    {
        mFullFilename = mFilename;
    }

    if( !mFilenameSchema.empty() )
    {
        mFullFilenameSchema     = "../data/" + mFilenameSchema;
    }

    size_t found = mFullFilename.find_last_of("/\\");
    mDirectory = (mFullFilename.substr(0, found)) + "/";

    //mHash = fileMD5(mFullFilename);

    iris::str_utils::OnlyFileName(mFilename);

	mExtension = mFullFilename;
	iris::str_utils::FileNameExtension(mExtension);
}

const std::string CResource::GetFileContent() const
{
    std::ifstream t(mFullFilename);
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}

CResourceNode CResource::GetRoot() const
{
	return CResourceNode( mRootNode );
}

bool CResource::Open()
{
	bool ok = true;
	if (!mDoc)
	{
		mDoc = new tinyxml2::XMLDocument();
		tinyxml2::XMLError eResult = mDoc->LoadFile(mFullFilename.c_str());
		ok = eResult == tinyxml2::XML_SUCCESS;
		if (ok)
		{
			mRootNode = mDoc->RootElement();
		}
		else
		{
			// TODO Process Errors here
		}
	}
	return ok;
}