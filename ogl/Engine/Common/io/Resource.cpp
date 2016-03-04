#include "Resource.h"

#include "Types.h"
#include "Logger/Logger.h"

namespace iris {
	namespace io
	{
		CResource::CResource(const std::string& aFilename, const std::string& aFileNameSchema)
			: mFilename(aFilename) 
			, mFilenameSchema(aFileNameSchema)
		{
		}

		//---------------------------------------------------------------------------------------------
		void CResource::Fill()
		{

			mFullFilename			= "../data/" + mFilename;
			mFullFilenameSchema     = "../data/" + mFilenameSchema;
			//mDirectory			=
			//mExtension			=
		}
	}
}