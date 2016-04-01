#include "StringUtils.h"

#include "Context.h"
#include "Logger/Logger.h"

#include "ogl.h"

CContext::CContext()
    : mOGLVersion("")
    , mGLSLVersion("")
{
}

CContext::~CContext()
{
}

bool CContext::Init()
{
    bool lOk(true);

    mOGLVendor   = (const char*)glGetString(GL_VENDOR);
    mOGLRenderer = (const char*)glGetString(GL_RENDERER);
    mOGLVersion  = (const char*)glGetString(GL_VERSION);
    mGLSLVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    // Init all the open gl functions
    ogl::InitOGLFunctions();

    //LOG_APPLICATION("Supported extensions:");
    int NumberOfExtensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

    for (int i = 0; i< NumberOfExtensions; ++i)
    {
        mExtensions.insert(std::string((const char*)ogl::glGetStringi(GL_EXTENSIONS, i)));
        //LOG_APPLICATION((const char*)(ogl::glGetStringi(GL_EXTENSIONS, i)));
    }

    return lOk;
}

const std::string& CContext::GetOGLVendor() const
{
    return mOGLVendor;
}

const std::string& CContext::GetOGLRenderer() const
{
    return mOGLRenderer;
}

const std::string& CContext::GetOGLVersion() const
{
    return mOGLVersion;
}

const std::string& CContext::GetGLSLVersion() const
{
    return mGLSLVersion;
}

bool CContext::IsCapable(Extension ar_extension) const
{
    return true;
}