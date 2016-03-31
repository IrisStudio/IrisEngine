#include "Texture.h"
#include "ogl.h"
#include "stb-master/stb_image.h"

#include "Logger\Logger.h"

CTexture::CTexture()
  : 
{
}

CTexture::~CTexture()
{
  glDeleteTextures(1, &mID);
}

void CTexture::Create(TextureType aType, const std::string& aFilename)
{
  unsigned char* data = stbi_load((aFilename).c_str(), &mWidth, &mHeight, &mNumComponents, 4);

  LOG_ERROR_IF(data == nullptr, "Unable to load texture %s");

  glGenTextures(1, &mID);
  glBindTexture(aType, mID);

  glTexParameteri(aType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(aType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameterf(aType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(aType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(aType, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
}

void CTexture::Bind()
{
  glBindTexture(GL_TEXTURE_2D, mID);
}