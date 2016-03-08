#ifndef __GAME_OBJECT_MANAGER__
#define __GAME_OBJECT_MANAGER__

#include <entityx/entityx.h>

#include "Singleton.h"

class CGameObjectManager : public entityx::EntityX, public Singleton<CGameObjectManager>
{
    public:
        CGameObjectManager();

        void update(entityx::TimeDelta dt);
};

#endif // __GAME_OBJECT_MANAGER__