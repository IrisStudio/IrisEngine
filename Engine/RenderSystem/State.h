#ifndef __IRIS_STATE__
#define __IRIS_STATE__

#include "Singleton.h"
#include "rs.h"
#include "Types.h"

class CState : public Singleton< CState >
{
    public:
        CState();
        virtual ~CState();

		inline const bool GetBlend() const
		{
			return mBlend;
		}
		inline const BlendEquation GetBlendEquation() const
		{
			return mBlendEquation;
		}
		inline const BlendFunc GetBlendFuncSrc() const
		{
			return mBlendFuncSrc;
		}
		inline const BlendFunc GetBlendFuncDst() const
		{
			return mBlendFuncDst;
		}
		inline const bool GetCullFace() const
		{
			return mCullFace;
		}
		inline const bool GetDepthTest() const
		{
			return mDepthTest;
		}
		inline const bool GetScissorTest() const
		{
			return mScissorTest;
		}

		void SetBlendEquation(const BlendEquation);
		void SetBlendFunc(const BlendFunc, const BlendFunc);

		void EnableBlend();
		void EnableCullFace();
		void EnableDepthTest();
		void EnableScissorTest();

		void DisableBlend();
		void DisableCullFace();
		void DisableDepthTest();
		void DisableScissorTest();

    private:
		bool mBlend;
		BlendEquation mBlendEquation;
		BlendFunc mBlendFuncSrc;
		BlendFunc mBlendFuncDst;
		bool mCullFace;
		bool mDepthTest;
		bool mScissorTest;
};

#endif
