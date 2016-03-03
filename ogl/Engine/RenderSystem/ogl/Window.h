#ifndef __OGL__WINDOW__
#define __OGL__WINDOW__

#include <loki/Singleton.h>

enum ESizeType
{
  eST_Windowed = 0,
  eST_FitDesktop,
  eST_FullScreen
};

class CWindowImpl
{
public:
  CWindowImpl();
  virtual ~CWindowImpl();

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

typedef Loki::SingletonHolder<CWindowImpl> CWindow;

#endif
