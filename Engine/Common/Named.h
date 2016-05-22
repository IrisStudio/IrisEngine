#ifndef _CNamed_
#define _CNamed_
#pragma once

#include "Types.h"

class CNamed
{
    public:

        CNamed()
            : mId("")
        {
        }

        CNamed( const std::string& aId )
            : mId( aId )
        {
        }

        virtual ~CNamed()
        {
        }

        inline const std::string& GetId() const
        {
            return mId;
        }

        inline void SetId(const std::string& aId)
        {
            mId = aId;
        }

    private:

        std::string mId;
};

#endif
