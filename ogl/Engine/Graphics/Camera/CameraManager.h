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

        inline void AddCamera( const std::string& aName, CCamera* aCamera )
        {
            mCameras.AddResource(aName, aCamera);
        }

    private:

        typedef CTemplatedVectorMapManager< CCamera > TCameras;
        TCameras mCameras;
};

#endif // __CCameraManager__