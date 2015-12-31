#include "Logger.h"
#include <Windows.h>
#include <string>

namespace debug
{
  CLogger::CLogger()
  {

  }

  CLogger::~CLogger()
  {

  }

  void CLogger::AddNewEntry(DebugLevelMsg aEntryLevel, const char* aEntryMsg)
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

    lMsg += aEntryMsg;
    lMsg += "\n";
    OutputDebugString(lMsg.c_str());
  }
}