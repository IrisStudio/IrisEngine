#ifndef __IRIS_STATE__
#define __IRIS_STATE__

#include "rs.h"
#include "Types.h"

class CState
{
    public:
        static const bool            GetBlend();
        static const BlendEquation   GetBlendEquation();
        static const BlendFunc       GetBlendFuncSrc();
        static const BlendFunc       GetBlendFuncDst();
        static const bool            GetCullFace();
        static const bool            GetDepthTest();
        static const bool            GetScissorTest();

        static void SetBlendEquation(const BlendEquation);
        static void SetBlendFunc    (const BlendFunc, const BlendFunc);

        static void EnableBlend();
        static void EnableCullFace();
        static void EnableDepthTest();
        static void EnableScissorTest();

        static void DisableBlend();
        static void DisableCullFace();
        static void DisableDepthTest();
        static void DisableScissorTest();

        static void ActivateTexture(uint32 aStageId);
        static void BindTexture(TextureType aType, uint32 aId);

        static void SetViewport(uint32 aX, uint32 aY, uint32 aWidth, uint32 aHeight);
		static void ClearBuffers(const float4& aClearColor, bool aColorBuffer, bool aDepthBuffer, bool aStencilBuffer);
};

#endif
