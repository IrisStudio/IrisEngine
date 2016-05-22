#include "ObjLoader.h"

#include "Logger/Logger.h"
#include "rs.h"

#include <algorithm>

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"
#include "Texture.h"

#include "model_obj.h"

#include<fstream>


CObjLoader::CObjLoader()
    : mVertexCount(0)
    , mNormalsCount(0)
    , mUVCount(0)
    , mTrianglesCount(0)
    , mFlags(0)
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
    mResource = aResource;
    mMaterial = aMaterial;
    mMesh = aMesh;
    /*
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

        uint32 lFlags             = eGD_Position | eGD_Normal | eGD_UV;
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
    */

    ModelOBJ importer;
    bool ret = importer.import(aResource.GetFullFilename().c_str());

    FILE *lFile = fopen(aResource.GetFullFilename().c_str(), "r");

    if(lFile)
    {
        GatherData(lFile);
    }

    fclose(lFile);

    /*
    if( ret )
    {
        if (!err.empty())   // `err` may contain warning message.
        {
            LOG_WARNING("%s", err.c_str());
        }

        for each (tinyobj::material_t material in materials)
        {
            CSubMaterialSPtr lSubMaterial( new CSubMaterial( eRP_DiffuseMap ) );
            CTextureSPtr lTexture( new CTexture() );
            lTexture->Create(eTT_2D, aResource.GetDirectory() + material.diffuse_texname);
            lSubMaterial->SetTexture(eTC_Diffuse, lTexture);
            aMaterial->AddSubMaterial(lSubMaterial);
        }

        const uint32 lMaterialsCount = aMaterial->GetSubMaterialsCount();

        if( lMaterialsCount == 0 )
        {
            CSubMaterialSPtr lSubMaterial(new CSubMaterial(eRP_DiffuseMap));
            lSubMaterial->SetDiffuseColor( float3(1.0, 0.0, 0.0) );
            aMaterial->AddSubMaterial(lSubMaterial);
        }

        aMesh->Resize(lMaterialsCount);

        for each (tinyobj::shape_t shape in shapes )
        {
            uint32 lFlags = eGD_Position | eGD_Normal;
            lFlags |= (shape.mesh.texcoords.empty()) ? 0 : eGD_UV;

            const uint32 lVertices = shape.mesh.positions.size() / 3;
            std::vector< float > lGeometryData = mCopyFunctions[lFlags]( lVertices, shape.mesh );

            CGeometrySPtr lGeometry(new CGeometry());
            lGeometry->Create(lFlags,
                              &lGeometryData[0],
                              &shape.mesh.indices[0],
                              lVertices,
                              shape.mesh.indices.size());
            aMesh->AddGeometry(0, lGeometry);
        }
    }*/

    return true;
}

void CObjLoader::GatherData(FILE* aFile)
{
    int v = 0;
    int vt = 0;
    int vn = 0;
    char buffer[256] = { 0 };
    std::string name;

    while (fscanf(aFile, "%s", buffer) != EOF)
    {
        switch (buffer[0])
        {
            case 'f':   // v, v//vn, v/vt, v/vt/vn.
                {
                    fscanf(aFile, "%s", buffer);

                    if (strstr(buffer, "//")) // v//vn
                    {
                        sscanf(buffer, "%d//%d", &v, &vn);
                        fscanf(aFile, "%d//%d", &v, &vn);
                        fscanf(aFile, "%d//%d", &v, &vn);

                        ++mTrianglesCount;

                        while (fscanf(aFile, "%d//%d", &v, &vn) > 0)
                        {
                            ++mTrianglesCount;
                        }
                    }
                    else if (sscanf(buffer, "%d/%d/%d", &v, &vt, &vn) == 3) // v/vt/vn
                    {
                        fscanf(aFile, "%d/%d/%d", &v, &vt, &vn);
                        fscanf(aFile, "%d/%d/%d", &v, &vt, &vn);

                        ++mTrianglesCount;

                        while (fscanf(aFile, "%d/%d/%d", &v, &vt, &vn) > 0)
                        {
                            ++mTrianglesCount;
                        }
                    }
                    else if (sscanf(buffer, "%d/%d", &v, &vt) == 2) // v/vt
                    {
                        fscanf(aFile, "%d/%d", &v, &vt);
                        fscanf(aFile, "%d/%d", &v, &vt);

                        ++mTrianglesCount;

                        while (fscanf(aFile, "%d/%d", &v, &vt) > 0)
                        {
                            ++mTrianglesCount;
                        }
                    }
                    else // v
                    {
                        fscanf(aFile, "%d", &v);
                        fscanf(aFile, "%d", &v);

                        ++mTrianglesCount;

                        while (fscanf(aFile, "%d", &v) > 0)
                        {
                            ++mTrianglesCount;
                        }
                    }
                }
                break;

            case 'm':   // mtllib
                fgets(buffer, sizeof(buffer), aFile);
                sscanf(buffer, "%s %s", buffer, buffer);
                name += buffer;
                ImportMaterials( mResource.GetDirectory() + buffer );
                break;

            case 'v':   // v, vt, or vn
                switch (buffer[1])
                {
                    case '\0':
                        fgets(buffer, sizeof(buffer), aFile);
                        ++mVertexCount;
                        break;

                    case 'n':
                        fgets(buffer, sizeof(buffer), aFile);
                        ++mNormalsCount;
                        break;

                    case 't':
                        fgets(buffer, sizeof(buffer), aFile);

                        ++mUVCount;

                    default:
                        break;
                }

                break;

            default:
                fgets(buffer, sizeof(buffer), aFile);
                break;
        }
    }

    uint32 lVertexComponents = 0;

    if(mVertexCount > 0)
    {
        mFlags |= eGD_Position;
        lVertexComponents += 3;
    }

    if (mNormalsCount > 0)
    {
        mFlags |= eGD_Normal;
        lVertexComponents += 3;
    }

    if (mUVCount > 0)
    {
        mFlags |= eGD_UV;
        lVertexComponents += 2;
    }

    // Allocate memory for the OBJ model data.
    mPositions.resize(mVertexCount);
    mUVs.resize(mUVCount);
    mNormals.resize(mNormalsCount);
    mVB.resize(mTrianglesCount * 3 * lVertexComponents);
    mIB.resize(mTrianglesCount * 3);
}

void CObjLoader::ImportMaterials(const std::string& aMaterialsFile)
{
    FILE *lFile = fopen(aMaterialsFile.c_str(), "r");

    if (lFile)
    {
        int illum = 0;
        int lMaterialsCount = 0;
        char buffer[256] = { 0 };

        // Count the number of materials in the MTL file.
        while (fscanf(lFile, "%s", buffer) != EOF)
        {
            switch (buffer[0])
            {
                case 'n': // newmtl
                    ++lMaterialsCount;
                    fgets(buffer, sizeof(buffer), lFile);
                    sscanf(buffer, "%s %s", buffer, buffer);
                    break;

                default:
                    fgets(buffer, sizeof(buffer), lFile);
                    break;
            }
        }

        rewind(lFile);

        if(lMaterialsCount)
        {
            CMaterial::TSubMaterials lSubMaterials(lMaterialsCount);
            lMaterialsCount = 0;

            CSubMaterialSPtr lSubMaterial;

            // Load the materials in the MTL file.
            while (fscanf(lFile, "%s", buffer) != EOF)
            {
                switch (buffer[0])
                {
                    case 'N': // Ns
                        fscanf(lFile, "%f", &lSubMaterial->mShininess);

                        // Wavefront .MTL file shininess is from [0,1000].
                        // Scale back to a generic [0,1] range.
                        lSubMaterial->mShininess /= 1000.0f;
                        break;

                    case 'K': // Ka, Kd, or Ks
                        switch (buffer[1])
                        {
                            case 'a': // Ka
                                fscanf(lFile, "%f %f %f",
                                       &lSubMaterial->mAmbientColor[0],
                                       &lSubMaterial->mAmbientColor[1],
                                       &lSubMaterial->mAmbientColor[2]);
                                break;

                            case 'd': // Kd
                                fscanf(lFile, "%f %f %f",
                                       &lSubMaterial->mDiffuseColor[0],
                                       &lSubMaterial->mDiffuseColor[1],
                                       &lSubMaterial->mDiffuseColor[2]);
                                break;

                            case 's': // Ks
                                fscanf(lFile, "%f %f %f",
                                       &lSubMaterial->mSpecularColor[0],
                                       &lSubMaterial->mSpecularColor[1],
                                       &lSubMaterial->mSpecularColor[2]);
                                break;

                            default:
                                fgets(buffer, sizeof(buffer), lFile);
                                break;
                        }

                        break;

                    case 'T': // Tr
                        switch (buffer[1])
                        {
                            case 'r': // Tr
                                fscanf(lFile, "%f", &lSubMaterial->mTransparency);
                                lSubMaterial->mTransparency = 1.0f - lSubMaterial->mTransparency;
                                break;

                            default:
                                fgets(buffer, sizeof(buffer), lFile);
                                break;
                        }

                        break;

                    case 'd':
                        fscanf(lFile, "%f", &lSubMaterial->mTransparency);
                        break;

                    case 'i': // illum
                        fscanf(lFile, "%d", &illum);

                        /*
                        if (illum == 1)
                        {
                            lSubMaterial->specular[0] = 0.0f;
                            lSubMaterial->specular[1] = 0.0f;
                            lSubMaterial->specular[2] = 0.0f;
                            lSubMaterial->specular[3] = 1.0f;
                        }
                        */

                        break;

                    case 'm': // map_Kd, map_bump
                        if (strstr(buffer, "map_Kd") != 0)
                        {
                            CTextureSPtr lTexture(new CTexture());
                            fgets(buffer, sizeof(buffer), lFile);
                            sscanf(buffer, "%s %s", buffer, buffer);
                            lTexture->Create(eTT_2D, mResource.GetDirectory() + buffer);
                            lSubMaterial->mTextures[eTC_Diffuse] = lTexture;
                        }
                        else if (strstr(buffer, "map_bump") != 0)
                        {
                            CTextureSPtr lTexture(new CTexture());
                            fgets(buffer, sizeof(buffer), lFile);
                            sscanf(buffer, "%s %s", buffer, buffer);
                            lTexture->Create(eTT_2D, mResource.GetDirectory() + buffer);
                            lSubMaterial->mTextures[eTC_Bump] = lTexture;
                        }
                        else
                        {
                            // TODO:: Handle more! :D
                            fgets(buffer, sizeof(buffer), lFile);
                        }

                        break;

                    case 'n': // newmtl
                        fgets(buffer, sizeof(buffer), lFile);
                        sscanf(buffer, "%s %s", buffer, buffer);

                        lSubMaterial = CSubMaterialSPtr(new CSubMaterial());
                        lSubMaterial->SetId(buffer);
                        lSubMaterials[lMaterialsCount] = lSubMaterial;
                        ++lMaterialsCount;
                        break;

                    default:
                        fgets(buffer, sizeof(buffer), lFile);
                        break;
                }
            }

            mMaterial->SetSubMaterials( lSubMaterials );
        }
        else // Create a default material
        {
            CSubMaterialSPtr lSubMaterial(new CSubMaterial());
            lSubMaterial->SetId("default");
            mMaterial->AddSubMaterial(lSubMaterial);
        }
    }

    fclose(lFile);
}