#ifndef __IO_RESOURCE__
#define __IO_RESOURCE__

#include <string>

namespace iris {
	namespace io
	{
		class CResource
		{
		public:
			CResource( const std::string& aFilename, const std::string& aFileNameSchema );

			inline const std::string& GetFilename()		  const;
			inline const std::string& GetFullFilename()	  const;
			inline const std::string& GetFullFilenameSchema() const;
			inline const std::string& GetDirectory()      const;
			inline const std::string& GetExtension()      const;

		private:
			std::string mFilename;
			std::string mFilenameSchema;
			std::string mFullFilename;
			std::string mFullFilenameSchema;
			std::string mDirectory;
			std::string mExtension;

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
		inline const std::string& CResource::GetFullFilename() const
		{
			return mFullFilename;
		}
	}
}

#endif // __IO_RESOURCE__
