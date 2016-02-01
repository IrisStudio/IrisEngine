#ifndef __LOGGER__
#define __LOGGER__

#include <loki/Singleton.h>

#define IRIS_LOG_APPLICATION(aEntryMsg) debug::CLogger::Instance().AddNewEntry( debug::eDL_Trace,      aEntryMsg );
#define IRIS_LOG_ERROR(aEntryMsg)       debug::CLogger::Instance().AddNewEntry( debug::eDL_Error,      aEntryMsg );
#define IRIS_LOG_WARNING(aEntryMsg)     debug::CLogger::Instance().AddNewEntry( debug::eDL_Warning,    aEntryMsg );
#define IRIS_LOG_ASSERT(aEntryMsg)      debug::CLogger::Instance().AddNewEntry( debug::eDL_Assertion,  aEntryMsg );

#define IRIS_LOG_ERROR_IF(aCondition, aEntryMsg) if( aCondition ) { debug::CLogger::Instance().AddNewEntry( debug::eDL_Error,      aEntryMsg ); };

namespace debug
{
  enum DebugLevelMsg
  {
    eDL_Warning = 0,
    eDL_Trace,
    eDL_Error,
    eDL_Assertion
  };

  class CLoggerImpl
  {
  public:
    CLoggerImpl(){}
    virtual ~CLoggerImpl(){}
    void AddNewEntry(DebugLevelMsg aEntryLevel, const char* aEntryMsg);

  private:
  };

  typedef Loki::SingletonHolder< CLoggerImpl > CLogger;
}

#endif // __LOGGER__
