#ifndef _string_utils_
#define _string_utils_

#include <Windows.h>
#include <string>

namespace iris { namespace str_utils
{
  inline std::string Format(const char* format, ...)
	{
	  va_list args;
	  char* buffer;
	  va_start( args, format );
	  int len = _vscprintf( format, args ) + 1;
	  buffer = ( char* )malloc( len * sizeof( char ) );
	  vsprintf_s( buffer, len, format, args );
    std::string output(buffer);
	  free(buffer);
	  va_end(args);
    return output;
	}

  inline void OnlyFileName(std::string& strPath, bool aRemoveExtension = true )
  {
	  const size_t last_slash_idx = strPath.find_last_of("\\/");
	  if (std::string::npos != last_slash_idx)
	  {
		  strPath.erase(0, last_slash_idx + 1);
	  }

	  if( aRemoveExtension )
	  {
		  // Remove extension if present.
		  const size_t period_idx = strPath.rfind('.');
		  if (std::string::npos != period_idx)
		  {
			  strPath.erase(period_idx);
		  }
	  }
  }
}}

#endif