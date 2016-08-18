#include "Scripting.h"
#include "Camera/Camera.h"

namespace scripting
{
	/*
	class Bar
	{
	public:
		Bar(float num)
		{
			x = num;
		}

		void SetX(float x2) {
			x = x2;
		}

		float GetX() const {
			return x;
		}
	private:
		float x;
	};

	template <> void Bind< CCamera >(sel::State& aState )
	{
		//aState["float"].SetClass<float>();
		aState["CCamera"].SetClass<CCamera>
			(
				"GetFOV", &CCamera::GetFOV,
				"SetFOV", &CCamera::SetFOV
			);

		aState["Bar"].SetClass<Bar, float>("SetX", &Bar::SetX, "GetX", &Bar::GetX);
	}
	*/
}

