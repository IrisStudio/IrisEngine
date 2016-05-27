#include "Texture.h"
#include "ogl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

#include "Logger\Logger.h"

namespace
{
	static const GLenum sTextureStageId[32] =
	{
		GL_TEXTURE0,
		GL_TEXTURE1,
		GL_TEXTURE2,
		GL_TEXTURE3,
		GL_TEXTURE4,
		GL_TEXTURE5,
		GL_TEXTURE6,
		GL_TEXTURE7,
		GL_TEXTURE8,
		GL_TEXTURE9,
		GL_TEXTURE10,
		GL_TEXTURE11,
		GL_TEXTURE12,
		GL_TEXTURE13,
		GL_TEXTURE14,
		GL_TEXTURE15,
		GL_TEXTURE16,
		GL_TEXTURE17,
		GL_TEXTURE18,
		GL_TEXTURE19,
		GL_TEXTURE20,
		GL_TEXTURE21,
		GL_TEXTURE22,
		GL_TEXTURE23,
		GL_TEXTURE24,
		GL_TEXTURE25,
		GL_TEXTURE26,
		GL_TEXTURE27,
		GL_TEXTURE28,
		GL_TEXTURE29,
		GL_TEXTURE30,
		GL_TEXTURE31
	};
}

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
    ogl::glActiveTexture(sTextureStageId[aStageId]);
    glBindTexture(mType, mID);
    ogl::CheckOGLError("After CTexture::Bind()");
}