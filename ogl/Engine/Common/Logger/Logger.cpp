#include "Logger.h"
#include <Windows.h>
#include <string>

namespace debug
{
  void CLoggerImpl::AddNewEntry(DebugLevelMsg aEntryLevel, const char* aEntryMsg, ... )
  {
    std::string lMsg;
    switch (aEntryLevel)
    {
    case eDL_Error:     lMsg = "[ERROR]";   break;
    case eDL_Warning:   lMsg = "[WARNING]"; break;
    case eDL_Trace:     lMsg = "[APP]";     break;
    case eDL_Assertion: lMsg = "[ASSERT]";  break;
    default:
      break;
    }

    va_list args;
    char* buffer;
    va_start(args, aEntryMsg);
    int len = _vscprintf(aEntryMsg, args) + 1;
    buffer = (char*)malloc(len * sizeof(char));
    vsprintf_s(buffer, len, aEntryMsg, args);

    lMsg += buffer + std::string("\n");
   

    OutputDebugString(lMsg.c_str());
    printf("%s", lMsg.c_str());

    free(buffer);
    va_end(args);
  }
}