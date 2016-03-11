#ifndef __OGL__WINDOW__
#define __OGL__WINDOW__

#include "Singleton.h"
#include "Types.h"

class CInputManager : public Singleton< CInputManager >
{
    public:
        CInputManager();
        virtual ~CInputManager();

    private:
};

#endif
