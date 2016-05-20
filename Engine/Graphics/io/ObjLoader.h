#pragma once
#ifndef _OBJ_LOADER_
#define _OBJ_LOADER_

#include "Types.h"
#include "io\Resource.h"

#include <functional>

class CMesh;
class CMaterial;

class CObjLoader
{
    public:
        CObjLoader();
        virtual ~CObjLoader();
        bool Load(const CResource& aResource, CMesh* aMesh, CMaterial* aMaterial );
    private:
        //std::map< uint32, std::function<std::vector< float >(const uint32&, const tinyobj::mesh_t&) > > mCopyFunctions;
        DISALLOW_COPY_AND_ASSIGN(CObjLoader);
};

#endif //_OBJ_LOADER_