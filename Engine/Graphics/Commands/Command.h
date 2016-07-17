#pragma once
#ifndef _CCommand_
#define _CCommand_

#include "Types.h"
#include "Named.h"

namespace gph
{
    class CCommand : public CNamed
    {
        public:
            CCommand( const std::string& aId );
            virtual ~CCommand();
            virtual void Execute() const = 0;

        protected:
        private:
            DISALLOW_COPY_AND_ASSIGN(CCommand);
    };
}

typedef std::shared_ptr< gph::CCommand > CGphCommandSPtr;

#endif