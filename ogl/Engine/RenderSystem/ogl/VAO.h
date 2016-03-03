#ifndef __OGL_VAO__
#define __OGL_VAO__

#include <Types.h>

class CVao
{
public:
  CVao();
  virtual ~CVao();
  void Create();
  uint32 GetID() const;

private:
  uint32 mID;
};

inline uint32 CVao::GetID() const { return mID; }

#endif
