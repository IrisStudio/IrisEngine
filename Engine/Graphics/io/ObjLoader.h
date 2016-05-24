#pragma once
#ifndef _OBJ_LOADER_
#define _OBJ_LOADER_

#include "Types.h"
#include "io\Resource.h"

#include "tiny_obj_loader.h"

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
        DISALLOW_COPY_AND_ASSIGN(CObjLoader);

        std::vector< float3 > mPositions;
        std::vector< float3 > mNormals;
        std::vector< float2 > mUVs;
        std::vector< float >  mVB;
        std::vector< uint32 > mIB;

        uint32 mVertexCount;
        uint32 mNormalsCount;
        uint32 mUVCount;
        uint32 mTrianglesCount;
        uint32 mFlags;
		uint32 mVertexSize;


        CResource  mResource;
        CMaterial* mMaterial;
        CMesh*     mMesh;

        void GatherData(FILE* aFile);
		void BuildMesh(FILE* aFile);
        void ImportMaterials( const std::string& aMaterialsFile );
		void AddVertex(uint32 aPosIdx, uint32 aNormalIdx, uint32 aUVIdx, uint32 & aiVertex, uint32 & aiTriangle, uint32 & aiTriangleId);

		typedef std::map< std::string, uint32 > TMaterialsCache;
		TMaterialsCache mMaterialsIds;
        std::map< uint32, std::function<std::vector< float >(const uint32&, const tinyobj::mesh_t&) > > mCopyFunctions;
};

#endif //_OBJ_LOADER_