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

        inline CCameraSPtr GetCamera(const std::string& aCameraName) const
        {
            return CCameraSPtr( mCameras.GetConstResource(aCameraName) );
        }

        inline void AddCamera(const std::string& aName, CCameraSPtr aCamera)
        {
            mCameras.AddResource(aName, aCamera);
        }

        inline void SetCurrentCamera(CCameraSPtr aCamera)
        {
            mCurrentCamera = aCamera;
        }

        inline CCameraSPtr GetCurrentCamera() const
        {
            return mCurrentCamera;
        }

    private:

        typedef CTemplatedVectorMapManager< CCameraSPtr > TCameras;
        TCameras mCameras;
        CCameraSPtr mCurrentCamera;
};

#endif // __CCameraManager__