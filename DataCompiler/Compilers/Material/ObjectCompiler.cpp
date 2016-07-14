#include "ObjectCompiler.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "StringUtils.h"

#include "gph.h"

#include <iostream>
#include <fstream>

#include "io/json.h"

// for convenience
using json = nlohmann::json;

#define GET_TEXTURE_FILE( type, tex_filename, flag ) \
    if (lSubMaterialPtr->GetTexture(type, 0, &tex_filename, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) \
    { \
        std::string filename(tex_filename.C_Str()); \
        OnlyFileName(filename, false); \
        tex_filename = filename;\
        lFlags |= flag; \
        writer["submaterials"][lName.C_Str()][EnumString< RenderableProperties >::ToStr( flag )] = filename; \
    }

struct SObjVertex
{
    float3 pos;
	float3 normal;
	float2 uv;
};

using namespace iris;
using namespace str_utils;

CObjectCompiler::CObjectCompiler()
    : CCompiler()
{

}

CObjectCompiler::~CObjectCompiler()
{
}

void CObjectCompiler::Compile(const CResource & aResource)
{
    // Create an instance of the Importer class
    Assimp::Importer importer;
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(aResource.GetFullFilename(),
		aiProcess_CalcTangentSpace |
		aiProcess_GenNormals |
		aiProcess_GenSmoothNormals |
		aiProcess_Triangulate |
		aiProcess_OptimizeGraph |
		aiProcess_OptimizeMeshes |
		aiProcess_FlipUVs);

    // If the import failed, report it
    if (scene)
    {
        aiString lName;
        aiColor3D lDiffuseColor;
        float     lTransparent;
        aiString  lAmbientMap;
        aiString  lDiffuseMap;
        aiString  lBumpMap;
        aiString  lSelfIlumMap;
        aiString  lDisplacementMap;
        aiString  lSpecularMap;
        aiString  lAlphaMap;
        uint32    lFlags;

        json writer;

        for (size_t i = 0; i < scene->mNumMaterials; ++i)
        {
            aiMaterial *lSubMaterialPtr = scene->mMaterials[i];

            lFlags = 0;

            lSubMaterialPtr->Get(AI_MATKEY_NAME, lName);

            if (strcmp(lName.C_Str(), "DefaultMaterial") != 0)
            {
                lSubMaterialPtr->Get(AI_MATKEY_COLOR_DIFFUSE, lDiffuseColor);
                lFlags != eRP_DiffuseColor;
                writer["submaterials"][lName.C_Str()]["diffuse_color"]["r"] = lDiffuseColor.r;
                writer["submaterials"][lName.C_Str()]["diffuse_color"]["g"] = lDiffuseColor.g;
                writer["submaterials"][lName.C_Str()]["diffuse_color"]["b"] = lDiffuseColor.b;

                lSubMaterialPtr->Get(AI_MATKEY_OPACITY, lTransparent);

                writer["submaterials"][lName.C_Str()]["transparent"] = bool(1 - lTransparent);

                if (lSubMaterialPtr->GetTextureCount(aiTextureType_DIFFUSE) > 0)
                {
                    GET_TEXTURE_FILE(aiTextureType_DIFFUSE, lDiffuseMap, eRP_DiffuseMap);
                    GET_TEXTURE_FILE(aiTextureType_DISPLACEMENT, lDisplacementMap, eRP_DisplacementMap);
                    GET_TEXTURE_FILE(aiTextureType_HEIGHT, lBumpMap, eRP_NormalMap);
                    GET_TEXTURE_FILE(aiTextureType_LIGHTMAP, lSelfIlumMap, eRP_SelfIlumMap);
                    GET_TEXTURE_FILE(aiTextureType_OPACITY, lAlphaMap, eRP_TransparentMap);
                }

                writer["submaterials"][lName.C_Str()]["renderable_properties"] = lFlags;
            }
        }

        CResource lMaterialResource(aResource.GetDirectory() + aResource.GetFilename() + ".mat");
        std::ofstream lMaterialFile(lMaterialResource.GetFullFilename().c_str());
        lMaterialFile << writer;
        lMaterialFile.close();

        CResource lMeshResource(aResource.GetDirectory() + aResource.GetFilename() + ".mesh");

		std::FILE* lMeshFile = 0;
		fopen_s(&lMeshFile, lMeshResource.GetFullFilename().c_str(), "wb");

        uint32 lMeshFlags = eGD_Position | eGD_Normal | eGD_UV;
		std::fwrite(&lMeshFlags, sizeof(uint32), 1, lMeshFile);

		uint32 lNumMeshes = scene->mNumMeshes;
		std::fwrite(&lNumMeshes, sizeof(uint32), 1, lMeshFile);

		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

        for (uint32 iMeshes = 0, lMeshesCount = scene->mNumMeshes; iMeshes < lMeshesCount; ++iMeshes)
        {
            aiMesh* lCurrentMesh = scene->mMeshes[iMeshes];

			uint32 lMaterialIdx = lCurrentMesh->mMaterialIndex;
			std::fwrite(&lMaterialIdx, sizeof(uint32), 1, lMeshFile);
			
			if( lMaterialIdx > 0 )
				--lMaterialIdx;

			uint32 lNumVertices = lCurrentMesh->mNumVertices;
			std::vector< SObjVertex > lGeometryData(lNumVertices);
			for (uint32 i = 0; i < lCurrentMesh->mNumVertices; ++i)
			{
				const aiVector3D* pPos = &(lCurrentMesh->mVertices[i]);
				const aiVector3D* pNormal = &(lCurrentMesh->mNormals[i]);
				const aiVector3D* pTexCoord = lCurrentMesh->HasTextureCoords(0) ? &(lCurrentMesh->mTextureCoords[0][i]) : &Zero3D;

				lGeometryData[i] = { float3(pPos->x, pPos->y, pPos->z), float3(pNormal->x, pNormal->y, pNormal->z), float2(pTexCoord->x, pTexCoord->y) };
			}

			std::fwrite(&lNumVertices, sizeof(uint32), 1, lMeshFile);
			std::fwrite(&lGeometryData[0], sizeof(SObjVertex), lNumVertices, lMeshFile);

			uint32 lNumFaces = lCurrentMesh->mNumFaces;
			std::vector< uint32 > lIndices;
			for (unsigned int i = 0; i < lCurrentMesh->mNumFaces; i++)
			{
				const aiFace& Face = lCurrentMesh->mFaces[i];
				assert(Face.mNumIndices == 3);
				lIndices.push_back(Face.mIndices[0]);
				lIndices.push_back(Face.mIndices[1]);
				lIndices.push_back(Face.mIndices[2]);
			}
			
			std::fwrite(&lNumFaces, sizeof(uint32), 1, lMeshFile);
			std::fwrite(&lIndices[0], sizeof(uint32), lNumFaces * 3, lMeshFile);
        }

		std::fclose(lMeshFile);
    }
}
