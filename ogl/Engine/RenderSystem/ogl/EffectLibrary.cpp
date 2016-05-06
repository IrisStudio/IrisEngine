#include "EffectLibrary.h"

#include "XML/XML.h"
#include "io/io.h"
#include "Shader.h"
#include "Effect.h"
#include "Logger/Logger.h"

#include <string>

namespace Shaders
{

#define begin_main "void main()\n{\n"
#define end_main "}\n"

    namespace VS
    {
        // Application to vertex shader uniforms
#define in_model            "layout(location = 0) uniform mat4 model;\n"
#define in_view             "layout(location = 1) uniform mat4 view;\n"
#define in_projection       "layout(location = 2) uniform mat4 projection;\n"

#define in_3d_position      "layout(location = 0) in vec3 position;\n"
#define in_2d_position      "layout(location = 0) in vec2 position;\n"
#define compute_3d_position "    gl_Position = projection * view * model * vec4(position, 1.0f);\n"
#define compute_2d_position "    gl_Position = vec4(position.xy, 0.0, 1.0);\n"

#define in_out_normal       "layout(location = 1) in vec3 normal;\n out vec3 Normal;\n"
#define interpolate_normal  "    Normal = normal;\n"

#define in_out_uv           "layout(location = 2) in vec2 uv;\nout vec2 ftexcoord;\n"
#define compute_uv          "    ftexcoord = uv;\n"

        const char* eGD_ScreenPosition_Str =
            in_2d_position
            begin_main
            compute_2d_position
            end_main;

        const char* eGD_ScreenPosition_UV_Str =
            in_2d_position
            in_out_uv
            begin_main
            compute_2d_position
            compute_uv
            end_main;

        const char* eGD_Position_Str =
            in_3d_position
            in_model
            in_view
            in_projection
            begin_main
            compute_3d_position
            end_main;

        const char* eGD_Position_UV_Str =
            in_3d_position
            in_out_uv
            in_model
            in_view
            in_projection
            begin_main
            compute_3d_position
            compute_uv
            end_main;

        const char* eGD_Position_UV_Normal_Str =
            in_3d_position
            in_out_uv
            in_out_normal
            in_model
            in_view
            in_projection
            begin_main
            compute_3d_position
            compute_uv
            interpolate_normal
            end_main;

        const char* eGD_Position_Normal_Str =
            in_3d_position
            in_model
            in_view
            in_projection
            begin_main
            compute_3d_position
            end_main;
    }

    namespace FS
    {
#define out_color        "out vec4 color;\n"
#define return_def_color "color = vec4(1.0);\n"

#define diffuse_sampler "layout(location = 1) uniform sampler2D diffuse;\n"
#define in_uv           "in vec2 ftexcoord;\n"
#define in_normal       "in vec3 Normal;\n"
#define return_uv       "color = texture(diffuse, ftexcoord);\n"
#define return_normal   "color = vec4( Normal.xyz, 1.0);\n"

        const char* eGD_Position_Str =
            out_color
            begin_main
            return_def_color
            end_main;

        const char* eGD_Position_UV_Str =
            out_color
            diffuse_sampler
            in_uv
            begin_main
            return_uv
            end_main;

        const char* eGD_Position_UV_Normal_Str =
            out_color
            diffuse_sampler
            in_uv
            in_normal
            begin_main
            return_normal
            end_main;
    }
}

CEffectLibrary::CEffectLibrary()
    : mScreenUV(nullptr)
{

}

void CEffectLibrary::Init()
{
    using namespace Shaders;
    mEmbedded[eGD_ScreenPosition] = new CEffect(VS::eGD_ScreenPosition_Str, FS::eGD_Position_Str);
    mEmbedded[eGD_Position] = new CEffect(VS::eGD_Position_Str, FS::eGD_Position_Str);
    mEmbedded[eGD_Position | eGD_UV] = new CEffect(VS::eGD_Position_UV_Str, FS::eGD_Position_UV_Str);
    mEmbedded[eGD_Position | eGD_UV | eGD_Normal] = new CEffect(VS::eGD_Position_UV_Normal_Str, FS::eGD_Position_UV_Normal_Str);
    mEmbedded[eGD_Position | eGD_Normal] = new CEffect(VS::eGD_Position_UV_Normal_Str, FS::eGD_Position_UV_Normal_Str);
    mEmbedded[eGD_ScreenPosition | eGD_UV] = new CEffect(VS::eGD_ScreenPosition_UV_Str, FS::eGD_Position_UV_Str);
}

CEffectLibrary::~CEffectLibrary()
{
}

CEffect* CEffectLibrary::CreateEffect(const char* aEffectFile)
{
    return nullptr;
}

CEffect* CEffectLibrary::GetEffect(uint32 aEffectFlags)
{
    using namespace Shaders;
    TMapEffects::iterator lItfind = mEmbedded.find(aEffectFlags);
    assert(lItfind != mEmbedded.end());
    return lItfind->second;
}
