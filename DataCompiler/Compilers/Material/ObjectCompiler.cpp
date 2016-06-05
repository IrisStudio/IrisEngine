#include "ObjectCompiler.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "material_generated.h"

#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include "StringUtils.h"

#include "gph.h"

#define GET_TEXTURE_FILE( type, tex_filename ) \
    if (lSubMaterialPtr->GetTexture(type, 0, &tex_filename, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) \
    { \
        std::string filename(tex_filename.C_Str()); \
        OnlyFileName(filename, false); \
        tex_filename = filename;\
    }

#define TO_FBB_STR( str ) builder.CreateString( str.C_Str() )
#define CONVERT_COLOR( color ) new float3( color.r, color.g, color.b )

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
    // propably to request more postprocessing than we do in this example.
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
        aiColor3D lAmbientColor;
        aiColor3D lDiffuseColor;
        aiColor3D lSpecularColor;
        uint8     lIlum;
        float     lShiness;
        float     lTransparent;
        aiString  lAmbientMap;
        aiString  lDiffuseMap;
        aiString  lBumpMap;
        aiString  lSelfIlumMap;
        aiString  lDisplacementMap;
        aiString  lSpecularMap;
        aiString  lSpecularHighligthMap;
        aiString  lAlphaMap;

        flatbuffers::FlatBufferBuilder builder;

        std::vector<flatbuffers::Offset<SubMaterial>> lSubmaterials;

        for (size_t i = 0; i < scene->mNumMaterials; ++i)
        {
            aiMaterial *lSubMaterialPtr = scene->mMaterials[i];

            lSubMaterialPtr->Get(AI_MATKEY_NAME, lName);
            lSubMaterialPtr->Get(AI_MATKEY_COLOR_AMBIENT, lAmbientColor);
            lSubMaterialPtr->Get(AI_MATKEY_COLOR_DIFFUSE, lDiffuseColor);
            lSubMaterialPtr->Get(AI_MATKEY_COLOR_SPECULAR, lSpecularColor);
            lSubMaterialPtr->Get(AI_MATKEY_SHADING_MODEL, lIlum);
            lSubMaterialPtr->Get(AI_MATKEY_SHININESS, lShiness);
            lSubMaterialPtr->Get(AI_MATKEY_OPACITY, lTransparent);

            if (lSubMaterialPtr->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                GET_TEXTURE_FILE(aiTextureType_DIFFUSE, lDiffuseMap);
                GET_TEXTURE_FILE(aiTextureType_AMBIENT, lAmbientMap);
                GET_TEXTURE_FILE(aiTextureType_DISPLACEMENT, lDisplacementMap);
                GET_TEXTURE_FILE(aiTextureType_NORMALS, lBumpMap);
                GET_TEXTURE_FILE(aiTextureType_LIGHTMAP, lSelfIlumMap);
                GET_TEXTURE_FILE(aiTextureType_OPACITY, lAlphaMap);
            }

            auto submaterial = CreateSubMaterial(
                                   builder,
                                   TO_FBB_STR(lName),
                                   CONVERT_COLOR(lAmbientColor),
                                   CONVERT_COLOR(lDiffuseColor),
                                   CONVERT_COLOR(lSpecularColor),
                                   CONVERT_COLOR(lSpecularColor), // TODO:Find transmitance
                                   lShiness,
                                   0.0,
                                   lTransparent,
                                   lIlum,
                                   TO_FBB_STR(lAmbientMap),
                                   TO_FBB_STR(lDiffuseMap),
                                   TO_FBB_STR(lSpecularMap),
                                   TO_FBB_STR(lSpecularMap),
                                   TO_FBB_STR(lBumpMap),
                                   TO_FBB_STR(lSelfIlumMap),
                                   TO_FBB_STR(lAlphaMap)
                               );
            lSubmaterials.push_back(submaterial);
        }

        builder.Finish(CreateMaterial(builder, builder.CreateVector(lSubmaterials)));

        std::ofstream myfile;
        CResource lMaterialResource(aResource.GetDirectory() + aResource.GetFilename() + ".mat");
        myfile.open(lMaterialResource.GetFullFilename().c_str(), std::ios::out | std::ios::app | std::ios::binary);
        myfile.write((char*)builder.GetBufferPointer(), builder.GetSize());
        myfile.close();
    }
}
