#include "ObjLoader.h"

#include "Logger/Logger.h"
#include "rs.h"

#include <algorithm>

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"
#include "Texture.h"

#include "model_obj.h"
#include "io/io.h"

#include<fstream>


CObjLoader::CObjLoader()
    : mVertexCount(0)
    , mNormalsCount(0)
    , mUVCount(0)
    , mTrianglesCount(0)
    , mFlags(0)
    , mVertexSize(0)
{
    mCopyFunctions[eGD_Position] = [](const uint32& nVertices, const tinyobj::mesh_t& aMesh) -> std::vector< float >
    {
        std::vector< float > lGeometryData(nVertices * 3, 0); // Positions

        for (uint32 i3 = 0; i3 < nVertices * 3; i3 += 3)
        {
            memcpy(&lGeometryData[i3], &aMesh.positions[i3], 3 * sizeof(float));
        }

        return lGeometryData;
    };

    mCopyFunctions[eGD_Position | eGD_Normal] = [](const uint32& nVertices, const tinyobj::mesh_t& aMesh) -> std::vector< float >
    {
        std::vector< float > lGeometryData(nVertices * 6, 0); // Positions + Normals

        for (uint32 i6 = 0, i3 = 0; i6 < nVertices * 6; i6 += 6, i3 += 3)
        {
            memcpy(&lGeometryData[i6], &aMesh.positions[i3], 3 * sizeof(float));
            memcpy(&lGeometryData[i6 + 3], &aMesh.normals[i3], 3 * sizeof(float));
        }

        return lGeometryData;
    };

    mCopyFunctions[eGD_Position | eGD_UV] = [](const uint32& nVertices, const tinyobj::mesh_t& aMesh) -> std::vector< float >
    {
        std::vector< float > lGeometryData(nVertices * 5, 0); // Positions + UV

        for (uint32 i5 = 0, i3 = 0, i2 = 0; i5 < nVertices * 5; i5 += 5, i3 += 3, i2 += 2)
        {
            memcpy(&lGeometryData[i5], &aMesh.positions[i3], 3 * sizeof(float));
            memcpy(&lGeometryData[i5 + 3], &aMesh.texcoords[i2], 2 * sizeof(float));
        }

        return lGeometryData;
    };

    mCopyFunctions[eGD_Position | eGD_Normal | eGD_UV] = [](const uint32& nVertices, const tinyobj::mesh_t& aMesh) -> std::vector< float >
    {
        std::vector< float > lGeometryData(nVertices * 8, 0); // Positions + Normals + UV

        for (uint32 i8 = 0, i3 = 0, i2 = 0; i8 < nVertices * 8; i8 += 8, i3 += 3, i2 += 2)
        {
            memcpy(&lGeometryData[i8], &aMesh.positions[i3], 3 * sizeof(float));
            memcpy(&lGeometryData[i8 + 3], &aMesh.normals[i3], 3 * sizeof(float));
            memcpy(&lGeometryData[i8 + 6], &aMesh.texcoords[i2], 2 * sizeof(float));
        }

        return lGeometryData;
    };
}

CObjLoader::~CObjLoader()
{
}

bool
CObjLoader::Load( const CResource& aResource, CMesh* aMesh, CMaterial* aMaterial )
{
    mMaterial = aMaterial;
    mMesh = aMesh;

    CResource lMaterialResource( aResource.GetDirectory() + aResource.GetFilename() + ".mat" );
	if( lMaterialResource.Open())
		io::Load(lMaterialResource, *aMaterial);

	CResource lMeshResource(aResource.GetDirectory() + aResource.GetFilename() + ".mesh");
	io::Load(lMeshResource, *aMesh);

    return true;
}
