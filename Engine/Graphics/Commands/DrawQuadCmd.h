#pragma once
#ifndef _CDrawCommand_
#define _CDrawCommand_

#include "Commands/Command.h"
#include "gph.h"

namespace gph
{
    class CDrawQuadCmd : public CCommand
    {
        public:
            CDrawQuadCmd( const std::string& aId);
            virtual ~CDrawQuadCmd();
            void Init(CMaterialSPtr aMaterial);
            virtual void Execute() const;

        protected:
            CMaterialSPtr mMaterial;
        private:
            DISALLOW_COPY_AND_ASSIGN(CDrawQuadCmd);
            CFullScreenQuadSPtr mQuad;
    };
}

typedef std::shared_ptr< gph::CCommand > CGphCommandSPtr;

#endif