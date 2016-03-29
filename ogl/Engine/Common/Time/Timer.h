#pragma once
#ifndef INC_TIMERMANAGER_H_
#define INC_TIMERMANAGER_H_

#include "Types.h"
#include "Singleton.h"

static const float s30FPS = 1.0f / 30.0f;
static const float s60FPS = 1.0f / 60.0f;

class CTimer : public Singleton< CTimer >
{
    public:

        CTimer(uint32 avgSamples);
        ~CTimer();

        void Update();

        float GetConstFrameTime() const { return 1.0f / (float) muSamples; }
        float GetElapsedTime() const { return mDeltaTime; }
        float GetSpeedFactor() const { return mSpeedFactor; }

        float GetTime() const { return mfTime; }
        float GetTimeMs() const { return mfTime * 1000.0f; }

        float GetFPS() const { return mFPS; }
        float GetMaxFPS() const { return mMaxFps; }
        float GetMinFPS() const { return mMinFps; }

    private:

        float         mDeltaTime;
        float         mFPS;
        float         mMinFps;
        float         mMaxFps;
        float         mfLastFps;
        float         mfFPSTime;
        float         mfTime;
        float         mdLastTime;
        uint32        mNumberFPSCount;
        float*        mDeltas;               // array of instant delta times
        uint32        muSamples;             // deltas arrays length
        uint32        muIndex;               // current array position
        float         mSpeedFactor;
};

#endif //INC_TIMERMANAGER_H_