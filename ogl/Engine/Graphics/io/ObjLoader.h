#pragma once
#ifndef _OBJ_LOADER_
#define _OBJ_LOADER_

#include "Types.h"
#include "io\Resource.h"

class CObjLoader
{
    public:
		CObjLoader();
        virtual ~CObjLoader();
		bool Load(const CResource& aResource);
    private:
        DISALLOW_COPY_AND_ASSIGN(CObjLoader);
};

#endif //_OBJ_LOADER_