#ifndef _FRAME_BUFFER_H
#define _FRAME_BUFFER_H

#include "Types.h"
#include "Singleton.h"
#include "rs.h"

class CFrameBuffer : public Singleton< CFrameBuffer >
{
    public:
        CFrameBuffer();
        virtual ~CFrameBuffer();
        void Create();
        void Bind();
    protected:
    private:
        DISALLOW_COPY_AND_ASSIGN(CFrameBuffer);
        uint32 mID;
};

#endif