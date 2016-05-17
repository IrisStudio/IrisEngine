#if defined(DEBUG) || defined(_DEBUG)
    #include <crtdbg.h>
#endif

#include <Windows.h>

#include "Application.h"
#include "Window.h"
#include "Time\Timer.h"

#include "GameObjectManager.h"
#include "Camera\CameraManager.h"

#include "StringUtils.h"

#include <gainput\gainput.h>

// Define your user buttons
enum Button
{
	ButtonMenu,
	ButtonConfirm,
	MouseX,
	MouseY
};

static const float sMaximumFrameRate = 60.0f;
static const float sMinimumFrameRate = 15.0f;
static const float sUpdateInterval = 1.0f / sMaximumFrameRate;
static const float sMaxCyclesPerFrame = sMaximumFrameRate / sMinimumFrameRate;
static const int   sMaxSamples = 50;

static int64     mFreq;
static int64     mLastTime;
static int       mSampleCount;
static float     mTimeScale;
static float     mActualElapsedTimeSec;
static float     mFrameTimes[sMaxSamples];

IApplication::IApplication()
    : mCyclesLeft(0.0f)
{
    mFreq = 0;
    mLastTime = 0;
    mSampleCount = 0;
    mTimeScale = 0.0f;
    mActualElapsedTimeSec = 0.0f;
}

IApplication::~IApplication()
{
}

void IApplication::Run()
{
    #if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(3837);
    #endif

    float lUpdateIterations = 0.0f;

    CWindow& lMainWindow = CWindow::Instance();
    CTimer&  lTimer = CTimer::Instance(10);

    if (lMainWindow.Create(eST_Windowed))
    {
        if (lMainWindow.Show())
        {
            //Testing the EntityX construction
            CGameObjectManager& game_object_manager = CGameObjectManager::Instance();

            CCameraSPtr lCamera(new CCamera());
            CCameraManager::Instance().AddCamera("current_cam", lCamera);
            CCameraManager::Instance().SetCurrentCamera(lCamera);

			// Setup Gainput
			gainput::InputManager manager;
			const uint2& lSize = lMainWindow.GetSize();
			manager.SetDisplaySize(lSize.x, lSize.y);
			gainput::DeviceId mouseId = manager.CreateDevice<gainput::InputDeviceMouse>();
			gainput::DeviceId keyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();

			gainput::InputMap map(manager);
			map.MapBool(ButtonMenu, keyboardId, gainput::KeyA );
			map.MapBool(ButtonConfirm, mouseId, gainput::MouseButtonLeft);
			map.MapFloat(MouseX, mouseId, gainput::MouseAxisX);
			map.MapFloat(MouseY, mouseId, gainput::MouseAxisY);

            while (lMainWindow.Update())
            {
				MSG msg;
				while (PeekMessage(&msg, lMainWindow.GetHandle(), 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);

					// Forward any input messages to Gainput
					manager.HandleMessage(msg);
				}

				manager.Update();

				if (map.GetBoolWasDown(ButtonMenu))
				{
					LOG_APPLICATION("Open Menu!!\n");
				}
				if (map.GetBoolWasDown(ButtonConfirm))
				{
					LOG_APPLICATION("Confirmed!!\n");
				}

				if (map.GetFloatDelta(MouseX) != 0.0f || map.GetFloatDelta(MouseY) != 0.0f)
				{
					LOG_APPLICATION("Mouse: %f, %f\n", map.GetFloat(MouseX), map.GetFloat(MouseY));
				}

                ProccessInputs();
                lTimer.Update();
                lMainWindow.SetWindowTitle(iris::str_utils::Format("FPS: %f", lTimer.GetFPS()));
                game_object_manager.update(lTimer.GetElapsedTime());


            }
        }
    }
}

void IApplication::ProccessInputs()
{

}

void IApplication::Update( const float dt )
{

}

void IApplication::Render()
{
    //sMainWindow.BeginRender();
    //sMainWindow.Clear(true, false, false);
    //sMainWindow.EndRender();
}

float IApplication::dt()
{
    int64 time = 0;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&time));
    float elapsedTimeSec = (time - mLastTime) * mTimeScale;
    mLastTime = time;

    if (fabsf(elapsedTimeSec - mActualElapsedTimeSec) < 1.0f)
    {
        memmove(&mFrameTimes[1], mFrameTimes, sizeof(mFrameTimes) - sizeof(mFrameTimes[0]));
        mFrameTimes[0] = elapsedTimeSec;

        if (mSampleCount< sMaxSamples)
        {
            ++mSampleCount;
        }
    }

    mActualElapsedTimeSec = 0.0f;

    for (int i = 0; i < mSampleCount; ++i)
    {
        mActualElapsedTimeSec += mFrameTimes[i];
    }

    if (mSampleCount> 0)
    {
        mActualElapsedTimeSec/= mSampleCount;
    }

    return mActualElapsedTimeSec;
}