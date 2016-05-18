#include "InputManager.h"
#include "Window.h"
#include "Logger\Logger.h"

#include <gainput\gainput.h>
#include <Windows.h>

// Setup Gainput
gainput::InputManager* manager = nullptr;
gainput::InputMap* map = nullptr;

CInputManager::CInputManager()
    : mWindow(nullptr)
{
}

CInputManager::~CInputManager()
{
    CHECKED_DELETE(manager);
    CHECKED_DELETE(map);
}

void CInputManager::ProcessInputs()
{
    assert(mWindow);
    MSG msg;

    while (PeekMessage(&msg, (HWND)mWindow->GetHandle(), 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Forward any input messages to Gainput
        manager->HandleMessage(msg);
    }

    manager->Update();

    /*if(DoAction(Forward))  LOG_APPLICATION("Going Forward!!");
    if(DoAction(Backward)) LOG_APPLICATION("Going Backward!!");

    float x = 0.0f, y = 0.0f;
    if(DoAction(MouseX, x)) LOG_APPLICATION("X: %f", x);
    if(DoAction(MouseY, y)) LOG_APPLICATION("Y: %f", y);
    */
}

void CInputManager::Init(CWindow* aWindow)
{
    mWindow = aWindow;

    if (!manager)
    {
        manager = new gainput::InputManager();
    }

    const uint2& lSize = mWindow->GetSize();
    manager->SetDisplaySize(lSize.x, lSize.y);
    gainput::DeviceId mouseId = manager->CreateDevice<gainput::InputDeviceMouse>();
    gainput::DeviceId keyboardId = manager->CreateDevice<gainput::InputDeviceKeyboard>();

    CHECKED_DELETE(map);

    map = new gainput::InputMap(*manager);
    map->MapBool(Forward, keyboardId, gainput::KeyW);
    map->MapBool(Left, keyboardId, gainput::KeyA);
    map->MapBool(Right, keyboardId, gainput::KeyD);
    map->MapBool(Backward, keyboardId, gainput::KeyS);
    map->MapBool(Up, keyboardId, gainput::KeyE);
    map->MapBool(Down, keyboardId, gainput::KeyQ);
    map->MapBool(Run, keyboardId, gainput::KeyShiftL);
    map->MapFloat(MouseX, mouseId, gainput::MouseAxisX);
    map->MapFloat(MouseY, mouseId, gainput::MouseAxisY);
    map->MapFloat(Fire, mouseId, gainput::MouseButtonLeft);
}

bool CInputManager::DoAction(Actions aAction)
{
    return map->GetBool(aAction);
}

bool CInputManager::DoAction(Actions aAction, float& aAmount)
{
    aAmount = map->GetFloatDelta(aAction);
    return (map->GetFloatDelta(aAction) != 0.0f);
}