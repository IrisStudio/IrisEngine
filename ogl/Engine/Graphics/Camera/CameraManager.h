#ifndef __CCameraManager__
#define __CCameraManager__

#include "Singleton.h"
#include "TemplatedVectorMapManager.h"
#include "Camera\Camera.h"

class CCameraManager : public Singleton<CCameraManager>
{
    public:
        CCameraManager();
        virtual ~CCameraManager();

        inline CCamera* GetCamera(const std::string& aCameraName) const
        {
            return mCameras.GetConstResource(aCameraName);
        }

        inline void AddCamera(const std::string& aName, CCamera* aCamera)
        {
            mCameras.AddResource(aName, aCamera);
        }

        inline void SetCurrentCamera(CCamera* aCamera)
        {
            mCurrentCamera = aCamera;
        }

        inline CCamera* GetCurrentCamera() const
        {
            return mCurrentCamera;
        }

    private:

        typedef CTemplatedVectorMapManager< CCamera* > TCameras;
        TCameras mCameras;
        CCamera* mCurrentCamera;
};

#endif // __CCameraManager__