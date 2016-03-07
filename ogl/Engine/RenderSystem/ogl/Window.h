#ifndef __OGL__WINDOW__
#define __OGL__WINDOW__

#include "Singleton.h"
#include "Types.h"


enum ESizeType
{
  eST_Windowed = 0,
  eST_FitDesktop,
  eST_FullScreen
};

class CWindow : public Singleton< CWindow >
{
public:
  CWindow();
  virtual ~CWindow();

  virtual bool Create( ESizeType aSizeType );
  bool Show();
  bool Update();
  void SetSize(const uint2& aSize);
  void BeginRender();
  void Clear( bool aColorBuffer, bool aDepthBuffer, bool aStencilBuffer );
  void EndRender();

private:
  const char* mName;
  uint2       mSize;
  float4      mClearColor;
};

#endif
