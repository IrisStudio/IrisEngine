#include "GameObjectManager.h"

#include "Components\DefaultComponents.h"
#include "Components\DefaultSystems.h"
#include "Window.h"

CGameObjectManager::CGameObjectManager()
{
    // Add systems
    systems.add<MovementSystem>();
    systems.add<RenderSystem>();
    systems.configure();

    entityx::Entity entity = entities.create();
    entity.assign<Transform>();
    entity.assign<Velocity>(float3(1.0f, 0.0f, 0.0f), 1.0f);
    entity.assign<Renderer>( "models/head/head.obj", eRP_Default );
}

void CGameObjectManager::update(entityx::TimeDelta dt)
{
    // Update systems
    systems.update<MovementSystem>(dt);

    // Render
    CWindow& lMainWindow = CWindow::Instance();
    lMainWindow.BeginRender();
    lMainWindow.Clear(true, true, true);

    systems.update<RenderSystem>(dt);

    lMainWindow.EndRender();
}