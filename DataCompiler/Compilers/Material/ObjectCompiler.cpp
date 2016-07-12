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
    aiVector3D pos;
    aiVector3D normal;
    aiVector2D uv;
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
                           aiProcess_Triangulate |
                           aiProcess_JoinIdenticalVertices |
                           aiProcess_GenSmoothNormals |
                           aiProcess_SortByPType |
                           aiProcess_OptimizeGraph |
                           aiProcess_OptimizeMeshes |
                           aiProcess_FlipUVs );

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

        std::ofstream lMeshFile;
        CResource lMeshResource(aResource.GetDirectory() + aResource.GetFilename() + ".mesh");
        lMeshFile.open(lMeshResource.GetFullFilename(), std::ios::out | std::ios::app | std::ios::binary);

        uint32 lMeshFlags = eGD_Position | eGD_Normal | eGD_UV;
        lMeshFile << lMeshFlags;

        lMeshFile << scene->mNumMeshes;

        for (uint32 iMeshes = 0, lMeshesCount = scene->mNumMeshes; iMeshes < lMeshesCount; ++iMeshes)
        {
            aiMesh* lCurrentMesh = scene->mMeshes[iMeshes];

            uint32 lFacesCount = lCurrentMesh->mNumFaces;
            std::vector< SObjVertex > lGeometryData;
            std::vector< uint32 > lIndices(lFacesCount * 3, 0);

            lMeshFile << lCurrentMesh->mMaterialIndex;

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

            lMeshFile << lGeometryData.size();
            lMeshFile.write((char*)&lGeometryData[0], lGeometryData.size() * sizeof(SObjVertex));

            lMeshFile << lIndices.size();
            lMeshFile.write((char*)&lIndices[0], lIndices.size() * sizeof(uint32));
        }

        lMeshFile.close();
    }
}
