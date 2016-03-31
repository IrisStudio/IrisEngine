#ifndef TEXTURE_H
#define TEXTURE_H

#include "Types.h"
#include "rs.h"

class CTexture
{
public:
  CTexture();
  virtual ~CTexture();
  void Create(TextureType aType, const std::string& filename);
  void Bind();
protected:
private:
  DISALLOW_COPY_AND_ASSIGN(CTexture);
	uint32 mID;
  int32 mHeight;
  int32 mWidth;
  int32 mNumComponents;
  TextureType mType;
};

#endif