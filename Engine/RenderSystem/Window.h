#ifndef __OGL__WINDOW__
#define __OGL__WINDOW__

#include "Singleton.h"
#include "Types.h"
#include "rs.h"

class CWindow : public Singleton< CWindow >
{
    public:
        CWindow();
        virtual ~CWindow();

        virtual bool Create(WindowSize aSizeType );
        bool Show();
        bool Update();
        void SetSize(const uint2& aSize);
        const uint2& GetSize() const;
        void* GetHandle();
        void BeginRender();
        void EndRender();
        void SetWindowTitle(const std::string& aWindowTitle);

    private:
        const char* mName;
        uint2       mSize;
        float4      mClearColor;
};

#endif
