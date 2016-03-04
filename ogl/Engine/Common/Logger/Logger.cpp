#include "Logger.h"
#include <Windows.h>
#include <string>

namespace debug
{
    void CLoggerImpl::AddNewEntry(DebugLevelMsg aEntryLevel, const char* aEntryMsg, ... )
    {
        std::string lMsg;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (aEntryLevel)
        {
            case eDL_Error:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                lMsg = "[ERROR]";
                break;

            case eDL_Warning:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
                lMsg = "[WARNING]";
                break;

            case eDL_Trace:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                lMsg = "[INFO]";
                break;

            case eDL_Assertion:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                lMsg = "[ASSERT]";
                break;

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
        printf("%s",lMsg.c_str());

        free(buffer);
        va_end(args);
    }
}