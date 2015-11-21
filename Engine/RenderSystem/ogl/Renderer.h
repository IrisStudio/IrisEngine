#ifndef __OGL_CONTEXT__
#define __OGL_CONTEXT__

#include <Types.h>

namespace renderer
{
  class CRenderer
  {
  public:
    CRenderer();
    virtual ~CRenderer();
    bool Create(uint32 aWidth, uint32 aHeight);
    bool Execute();
    void Terminate();
  };
}

#endif
