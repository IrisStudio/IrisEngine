#include "GameObjectManager.h"

#include "Components\DefaultComponents.h"
#include "Components\DefaultSystems.h"

CGameObjectManager::CGameObjectManager()
{
    // Add systems
    systems.add<MovementSystem>();
    systems.configure();

    entityx::Entity entity = entities.create();
    entity.assign<Transform>();
    entity.assign<Velocity>(float3(1.0f, 0.0f, 0.0f), 1.0f);
}

void CGameObjectManager::update(entityx::TimeDelta dt)
{
    // Update systems
    systems.update<MovementSystem>(dt);
}