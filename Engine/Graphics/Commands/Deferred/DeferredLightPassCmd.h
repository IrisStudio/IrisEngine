#pragma once
#ifndef _CDefferedLightPassCommand_
#define _CDefferedLightPassCommand_

#include "Commands/DrawQuadCmd.h"

namespace gph
{
    class CDeferredLightPassCmd : public CDrawQuadCmd
    {
        public:
            CDeferredLightPassCmd();
            virtual ~CDeferredLightPassCmd();
            void Init();
            virtual void Execute() const;
        protected:
        private:
            DISALLOW_COPY_AND_ASSIGN(CDeferredLightPassCmd);
    };
}

typedef std::shared_ptr< gph::CCommand > CGphCommandSPtr;

#endif