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
}}

#endif