#include "GameObjectManager.h"

#include "Components\DefaultComponents.h"

CGameObjectManager::CGameObjectManager()
{
    // Add systems
    //systems.add<DebugSystem>();
    systems.configure();

    entityx::Entity entity = entities.create();
    entity.assign<Transform>();

}

void CGameObjectManager::update(entityx::TimeDelta dt)
{
    // Update systems
    //systems.update<DebugSystem>(dt);
    int a = 0;
    a++;
}