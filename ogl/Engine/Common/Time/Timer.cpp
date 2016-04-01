#include <Windows.h>
#include <timeapi.h>
#include <assert.h>
#include <float.h>
#include "Timer.h"

//Inicializamos todas las variables
CTimer::CTimer (uint32 avgSamples)
    : muSamples(avgSamples)
    , mDeltaTime(0.0f)
    , mfTime(0.0f)
    , mdLastTime(0)
    , mFPS(0.0f)
    , mfFPSTime(0.0f)
    , mNumberFPSCount(0)
    , mfLastFps(0.0f)
    , muIndex(0)
    , mMinFps(FLT_MAX)
    , mMaxFps(-FLT_MAX)
    , mSpeedFactor(1.0f)
{
    mDeltas = new float[muSamples];
    for(uint32 j=0;j<muSamples;j++)
    {
            mDeltas[j] = 0;
    }
}

CTimer::~CTimer( void )
{
    delete[] mDeltas;
}

// Actualiza los valores FPS, deltaTime y los timers (los normales y los inputs)
void CTimer::Update( void )
{
    //-----Actualizacion de los valores FPS y ElpasedTime-----
    //Calculo de la diferencia de tiempo (mfElpasedTime)
    float  ldCurTime = (float) timeGetTime();

    if( mdLastTime == 0 ) 
        mdLastTime = ldCurTime;

    mDeltas[muIndex] = (float)((ldCurTime - mdLastTime) * 0.001);
    mdLastTime = ldCurTime;


    float d = 0;
    for(unsigned int j=0; j<muSamples; j++)
    {
            d += mDeltas[j];
    }

    d /= (float)muSamples;
    mDeltaTime = d;

    mfTime += mDeltaTime;
    muIndex = (++muIndex) % muSamples;

    //Calculo de los frames por segundo (mFPS)
    mNumberFPSCount++;
    mfFPSTime += mDeltaTime;

    mFPS = (mfFPSTime > 0.0f ) ? mNumberFPSCount/mfFPSTime : 0.0f;

    mSpeedFactor = muSamples / (1.0f / mDeltaTime);
    if(mSpeedFactor <= 0.0f) mSpeedFactor = 1.0f;

    if( ldCurTime - mfLastFps > 1000 )    //Solo mostramos los fps cada segundo
    {
            mFPS = mNumberFPSCount/mfFPSTime;
            mNumberFPSCount = 0;
            mfFPSTime = 0;
            mfLastFps = (float)ldCurTime;
            if( mNumberFPSCount > 0 )
            {
                mMinFps = ( mMinFps < mFPS ) ? mMinFps : mFPS;
                mMaxFps = ( mMaxFps > mFPS ) ? mMaxFps : mFPS;
            }
    }
    //---------------------------------------------//

    if( mDeltaTime > s60FPS )
        mDeltaTime = s60FPS;
}