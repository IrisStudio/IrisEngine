#include "GameObjectManager.h"

#include "Components\DefaultComponents.h"
#include "Components\DefaultSystems.h"
#include "Window.h"

CGameObjectManager::CGameObjectManager()
{
    // Add systems
    systems.add<MovementSystem>();
    systems.add<RenderSystem>();
    systems.add<CameraSystem>();
    systems.configure();

    // Create mesh object
    entityx::Entity entity = entities.create();
    entity.assign<Transform>();
    entity.assign<Velocity>(float3(1.0f, 0.0f, 0.0f), 1.0f);
    entity.assign<Renderer>( "models/deadpool/deadpool.obj", eRP_Default );

    //Create camera object
    entity = entities.create();
    entity.assign<Transform>( float3(5.0f, 0.0f, 0.0f), float3(-1.0f, 0.0f, 0.0f) );
    entity.assign<CCamera>();
    entity.assign<Controllable>();
    CCameraManager::Instance().SetCurrentCamera(entity.component<CCamera>().get());
}

void CGameObjectManager::update(entityx::TimeDelta dt)
{
    // Update systems
    systems.update<MovementSystem>(dt);

    // Render
    CWindow& lMainWindow = CWindow::Instance();
    lMainWindow.BeginRender();
    lMainWindow.Clear(true, true, true);

    systems.update<CameraSystem>(dt);
    systems.update<RenderSystem>(dt);

    lMainWindow.EndRender();
}