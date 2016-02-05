#ifndef _IRIS_APP_
#define _IRIS_APP_

#include "Types.h"

class IApplication
{
public:
  
  enum EDisplayType
  {
    eDT_Windowed = 0,
    eDT_FullScreen
  };

public:
  IApplication();
  virtual ~IApplication();

  void Init(EDisplayType aDisplayType);
  void ProccessInputs();
  void Update( const float dt );
  void Render();
  void Run();

private:
  DISALLOW_COPY_AND_ASSIGN(IApplication);
  
  static float dt();
  float        mCyclesLeft;
};

#endif