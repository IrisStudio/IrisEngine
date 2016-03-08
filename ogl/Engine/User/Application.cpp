#if defined(DEBUG) || defined(_DEBUG)
    #include <crtdbg.h>
#endif

#include <Windows.h>

#include "Application.h"
#include "Window.h"

#include "Effect.h"
#include "EffectLibrary.h"

#include "io/Resource.h"

#include "ogl.h"

#include "GameObjectManager.h"

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
    //_CrtSetBreakAlloc(4427);
    #endif

    float lUpdateIterations = 0.0f;

    CWindow& lMainWindow = CWindow::Instance();

    if (lMainWindow.Create(eST_Windowed))
    {
        if (lMainWindow.Show())
        {
            QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFreq));
            QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mLastTime));
            mTimeScale = 1.0f / mFreq;

            /*CEffectLibrary lLib;
            CEffectSPtr lEffect = lLib.CreateEffect("../data/effects/effect01.xml");*/

            GLuint VBO;
            ogl::glGenBuffers(1, &VBO);

            float points[] =
            {
                0.0f,  0.5f,  0.0f,
                0.5f, -0.5f,  0.0f,
                -0.5f, -0.5f,  0.0f
            };

            ogl::CHECK_OGL_ERROR("Before all");
            GLuint vbo = 0;
            ogl::glGenBuffers(1, &vbo);
            ogl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
            ogl::glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
            ogl::CHECK_OGL_ERROR("after vbo");

            GLuint vao = 0;
            ogl::CHECK_OGL_ERROR("before vao");
            ogl::glGenVertexArrays(1, &vao);
            ogl::glBindVertexArray(vao);
            ogl::glEnableVertexAttribArray(0);
            ogl::glBindBuffer(GL_ARRAY_BUFFER, vbo);
            ogl::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            ogl::CHECK_OGL_ERROR("after vao");

            iris::io::CResource vert("shaders/first_triangle/ft.vert");
            const std::string lVtxShaderSrc( vert.GetFileContent() );
            CShaderSPtr lVertexShader(new CShader());
            lVertexShader->Create(ShaderType::eST_Vertex, lVtxShaderSrc.c_str() );

            iris::io::CResource frag("shaders/first_triangle/ft.frag");
            const std::string lFragShaderSrc(frag.GetFileContent());
            CShaderSPtr lFragmentShader(new CShader());
            lFragmentShader->Create(ShaderType::eST_Fragment, lFragShaderSrc.c_str() );

            CEffectSPtr lEffect(new CEffect( lVertexShader, lFragmentShader ));

            //Testing the EntityX construction
            CGameObjectManager& game_object_manager = CGameObjectManager::Instance();

            while (lMainWindow.Update())
            {
                ProccessInputs();

                // Update
                lUpdateIterations = dt() + mCyclesLeft;

                if (lUpdateIterations > sMaxCyclesPerFrame * sUpdateInterval )
                {
                    lUpdateIterations = sMaxCyclesPerFrame * sUpdateInterval;
                }

                while (lUpdateIterations > sUpdateInterval)
                {
                    lUpdateIterations -= sUpdateInterval;
                    Update( sUpdateInterval );

                    game_object_manager.update(sUpdateInterval);
                }

                mCyclesLeft = lUpdateIterations;

                lMainWindow.BeginRender();
                lMainWindow.Clear(true, false, false);
                ogl::CHECK_OGL_ERROR("Setting effect");
                lEffect->Bind();
                ogl::CHECK_OGL_ERROR("berfore seting vao");
                ogl::glBindVertexArray(vao);
                ogl::CHECK_OGL_ERROR("before draw");
                glDrawArrays(GL_TRIANGLES, 0, 3);
                ogl::CHECK_OGL_ERROR("after draw");
                ogl::glBindVertexArray(0);
                ogl::CHECK_OGL_ERROR("End loop");

                lMainWindow.EndRender();

                //Render();
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