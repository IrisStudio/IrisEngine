#include "ObjLoader.h"

#include "Logger/Logger.h"
#include "rs.h"

#include <algorithm>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"
#include "Texture.h"

CObjLoader::CObjLoader()
{
	/*
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
	*/
}

CObjLoader::~CObjLoader()
{
}

struct SObjVertex
{
	aiVector3D pos;
	aiVector3D normal;
	aiVector2D uv;
};

bool
CObjLoader::Load( const CResource& aResource, CMesh* aMesh, CMaterial* aMaterial )
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	const aiScene* scene= importer.ReadFile(aResource.GetFullFilename(), aiProcess_Triangulate | aiProcess_FlipUVs );

	// If the import failed, report it
	if (!scene)
	{
		LOG_ERROR(importer.GetErrorString());
		return false;
	}

	
	for (uint32 iMaterial = 0, lMaterialsCount = scene->mNumMaterials; iMaterial < lMaterialsCount; ++iMaterial)
	{
		const aiMaterial* lCurrentMaterial = scene->mMaterials[iMaterial];
		int a = 5;
		int texIndex = 0;
		aiString path;
		
		CSubMaterialSPtr lSubMaterial(new CSubMaterial(eRP_DiffuseMap));
		if (lCurrentMaterial->GetTexture(aiTextureType_DIFFUSE, texIndex, &path) == AI_SUCCESS)
		{
			CTextureSPtr lTexture(new CTexture());
			lTexture->Create(eTT_2D, aResource.GetDirectory() + path.data);
			lSubMaterial->SetTexture(eTC_Diffuse, lTexture);
		}

		aMaterial->AddSubMaterial(lSubMaterial);

	}

	aMesh->Resize( aMaterial->GetSubMaterialsCount() );

	for (uint32 iMeshes = 0, lMeshesCount = scene->mNumMeshes; iMeshes < lMeshesCount; ++iMeshes)
	{
		aiMesh* lCurrentMesh = scene->mMeshes[iMeshes];

		uint32 lFlags	          = eGD_Position | eGD_Normal | eGD_UV;
		uint32 lFacesCount        = lCurrentMesh->mNumFaces;
		std::vector< SObjVertex > lGeometryData;
		std::vector< uint32 > lIndices(lFacesCount * 3, 0);

		for (uint32 iFaces = 0, iVertex = 0; iFaces < lFacesCount; ++iFaces)
		{
			const aiFace& lCurrentFace = lCurrentMesh->mFaces[iFaces];
			// Copy the index buffer
			memcpy(&lIndices[iFaces * 3], &(lCurrentFace.mIndices[0]), 3 * sizeof(uint32));

			// Copy the vertex buffer
			for (uint32 iTriangle = 0; iTriangle < 3; ++iTriangle, ++iVertex)
			{
				SObjVertex lVertex;
				lVertex.pos = lCurrentMesh->mVertices[lCurrentFace.mIndices[iTriangle]];
				lVertex.normal = lCurrentMesh->HasNormals() ? lCurrentMesh->mNormals[lCurrentFace.mIndices[iTriangle]] : aiVector3D(1.0f, 1.0f, 1.0f);
				memcpy(&(lVertex.uv), &lCurrentMesh->mTextureCoords[0][lCurrentFace.mIndices[iTriangle]], sizeof(aiVector2D));
				lGeometryData.push_back(lVertex);
			}
		}

		CGeometrySPtr lGeometry(new CGeometry());
		lGeometry->Create(lFlags,
						  &lGeometryData[0],
						  &lIndices[0],
						  lGeometryData.size(),
						  lIndices.size());
		aMesh->AddGeometry(lCurrentMesh->mMaterialIndex, lGeometry);
	}

	
	return true;
}