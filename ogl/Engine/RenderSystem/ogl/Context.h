#ifndef __OGL__CONTEXT__
#define __OGL__CONTEXT__

#include "Singleton.h"
#include "ogl_ext.h"
#include "Types.h"

class CContext : public Singleton< CContext >
{
public:
  CContext();
  virtual ~CContext();

  bool Init();
  
  const std::string& GetOGLVendor() const;
  const std::string& GetOGLRenderer() const;
  const std::string& GetOGLVersion() const;
  const std::string& GetGLSLVersion() const;
  void               SetGLSLVersion(const std::string& ar_version );
  bool  IsCapable( ogl::Extension ar_extension) const;

private:
  std::string mOGLVersion;
  std::string mGLSLVersion;
  std::string mOGLVendor;
  std::string mOGLRenderer;
};

#endif
