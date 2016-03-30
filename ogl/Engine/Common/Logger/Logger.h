#ifndef __LOGGER__
#define __LOGGER__

#include "Singleton.h"

#define LOG_APPLICATION(aEntryMsg, ... ) debug::CLogger::Instance().AddNewEntry( debug::eDL_Trace,      aEntryMsg, __VA_ARGS__ );
#define LOG_ERROR(aEntryMsg, ... )       debug::CLogger::Instance().AddNewEntry( debug::eDL_Error,      aEntryMsg, __VA_ARGS__ );
#define LOG_WARNING(aEntryMsg, ... )     debug::CLogger::Instance().AddNewEntry( debug::eDL_Warning,    aEntryMsg, __VA_ARGS__ );
#define LOG_ASSERT(aEntryMsg, ... )      debug::CLogger::Instance().AddNewEntry( debug::eDL_Assertion,  aEntryMsg, __VA_ARGS__ );

#define LOG_ERROR_IF(aCondition, aEntryMsg, ... ) if( aCondition ) { debug::CLogger::Instance().AddNewEntry( debug::eDL_Error,      aEntryMsg, __VA_ARGS__ ); };

namespace debug
{
    enum DebugLevelMsg
    {
        eDL_Warning = 0,
        eDL_Trace,
        eDL_Error,
        eDL_Assertion
    };

    class CLogger : public Singleton< CLogger >
    {
        public:
            CLogger() {}
            virtual ~CLogger() {}
            void AddNewEntry(DebugLevelMsg aEntryLevel, const char* aEntryMsg, ... );

        private:
    };
}

#endif // __LOGGER__
