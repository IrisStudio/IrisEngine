#include "Texture.h"
#include "ogl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

#include "Logger\Logger.h"
#include "State.h"

CTexture::CTexture()
    : mWidth(0)
    , mHeight(0)
    , mNumComponents(0)
    , mType(eTT_2D)
{
}

CTexture::~CTexture()
{
    glDeleteTextures(1, &mID);
}

void CTexture::Create(TextureType aType, const std::string& aFilename)
{
    ogl::CheckOGLError("Before CTexture::Create");
    unsigned char* data = stbi_load(aFilename.c_str(), &mWidth, &mHeight, &mNumComponents, 4);

    LOG_ERROR_IF(data == nullptr, "Unable to load texture %s", aFilename.c_str() );

    glGenTextures(1, &mID);
    glBindTexture(aType, mID);

    glTexParameteri(aType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(aType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(aType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(aType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(aType, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    ogl::CheckOGLError("After CTexture::Create");
}

void CTexture::Bind(uint32 aStageId)
{
    ogl::CheckOGLError("Before CTexture::Bind()");
    CState::ActivateTexture(aStageId);
    CState::BindTexture(mType, mID);
    ogl::CheckOGLError("After CTexture::Bind()");
}