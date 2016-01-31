#ifndef __OGL__WINDOW__
#define __OGL__WINDOW__

#include <loki/Singleton.h>
#include <set>

class CWindowImpl
{
public:
  CWindowImpl();
  virtual ~CWindowImpl();

  virtual bool Create();
  bool Show();
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
