#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

#include <Windows.h>

#include "Application.h"
#include "Window.h"

#include "Effect.h"
#include "EffectLibrary.h"

static CWindowImpl sMainWindow = CWindow::Instance();
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

struct TSimpleVertex
{
  float x, y;
  float r, g, b, a;
};

TSimpleVertex quad[] =
{
  { 1.0f, 0.0f, 1.0f, 1.0f ,-0.4f,  0.4f } ,
  { 0.0f, 0.0f, 1.0f, 1.0f ,-0.4f, -0.4f } ,
  { 0.0f, 0.0f, 1.0f, 1.0f , 0.4f,  0.4f } ,
  { 0.0f, 0.0f, 1.0f, 1.0f , 0.4f, -0.4f }
};

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
#endif

  float lUpdateIterations = 0.0f;
  if (sMainWindow.Create(eST_Windowed))
  {
    if (sMainWindow.Show())
    {
      QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFreq));
      QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mLastTime));
      mTimeScale = 1.0f / mFreq;

      CEffectLibrary lLib;
      CEffectSPtr lEffect = lLib.CreateEffect("../data/effects/effect01.xml");

      while (sMainWindow.Update())
      {
        ProccessInputs();

        // Update
        lUpdateIterations = dt() + mCyclesLeft;

        if (lUpdateIterations > sMaxCyclesPerFrame * sUpdateInterval )
          lUpdateIterations = sMaxCyclesPerFrame * sUpdateInterval;
        
        while (lUpdateIterations > sUpdateInterval)
        {
          lUpdateIterations -= sUpdateInterval;
          Update( sUpdateInterval );
        }

        mCyclesLeft = lUpdateIterations;

        Render();
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
  sMainWindow.BeginRender();
  sMainWindow.Clear(true, false, false);
  sMainWindow.EndRender();
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
      ++mSampleCount;
  }

  mActualElapsedTimeSec = 0.0f;

  for (int i = 0; i < mSampleCount; ++i)
    mActualElapsedTimeSec += mFrameTimes[i];

  if (mSampleCount> 0)
    mActualElapsedTimeSec/= mSampleCount;

  return mActualElapsedTimeSec;
}