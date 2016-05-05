#pragma once
#ifndef _OBJ_LOADER_
#define _OBJ_LOADER_

#include "Types.h"
#include "io\Resource.h"
#include "Mesh\Mesh.h"

#include "tinyobjloader/tiny_obj_loader.h"

#include <functional>

class CObjLoader
{
    public:
        CObjLoader();
        virtual ~CObjLoader();
        bool Load(const CResource& aResource, CMesh& aMesh );
    private:
        std::map< uint32, std::function<std::vector< float >(tinyobj::mesh_t) > > mCopyFunctions;
        DISALLOW_COPY_AND_ASSIGN(CObjLoader);
};

#endif //_OBJ_LOADER_