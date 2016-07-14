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
    mResource = aResource;
    mMaterial = aMaterial;
    mMesh = aMesh;

    CResource lMaterialResource( aResource.GetDirectory() + aResource.GetFilename() + ".mat" );
    io::Load(lMaterialResource, *aMaterial);

	CResource lMeshResource(aResource.GetDirectory() + aResource.GetFilename() + ".mesh");
	io::Load(lMeshResource, *aMesh);

    return true;
}

void CObjLoader::GatherData(FILE* aFile)
{
    int v = 0;
    int vt = 0;
    int vn = 0;
    char buffer[256] = { 0 };

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

    if(mVertexCount > 0)
    {
        mFlags |= eGD_Position;
        mVertexSize += 3;
    }

    if (mNormalsCount > 0)
    {
        mFlags |= eGD_Normal;
        mVertexSize += 3;
    }

    if (mUVCount > 0)
    {
        mFlags |= eGD_UV;
        mVertexSize += 2;
    }

    // Allocate memory for the OBJ model data.
    mPositions.resize(mVertexCount);
    mUVs.resize(mUVCount);
    mNormals.resize(mNormalsCount);
    mVB.resize(mTrianglesCount * 3 * mVertexSize);
    mIB.resize(mTrianglesCount * 3);

    // Add a default material
    if (mMaterial->GetSubMaterialsCount() == 0)
    {
        CSubMaterialSPtr lSubMaterial(new CSubMaterial());
        lSubMaterial->SetId("default");
        lSubMaterial->SetRenderProperties(eRP_DiffuseMap);
        CTextureSPtr lTexture( new CTexture() );
        lTexture->Create(eTT_2D, "../data/tex/uv.jpg");
        lSubMaterial->mTextures[eTC_Diffuse] = lTexture;
        mMaterial->AddSubMaterial(lSubMaterial);
    }

    mMesh->Resize(mMaterial->GetSubMaterialsCount());
}

void CObjLoader::AddVertex(uint32 aPosIdx, uint32 aNormalIdx, uint32 aUVIdx, uint32& aiVertex, uint32& aiTriangle, uint32& aiTriangleId)
{
    memcpy(&mVB[aiVertex], &mPositions[--aPosIdx], sizeof(float3));
    aiVertex += 3;
    memcpy(&mVB[aiVertex], &mNormals[--aNormalIdx], sizeof(float3));
    aiVertex += 3;
    memcpy(&mVB[aiVertex], &mUVs[--aUVIdx], sizeof(float2));
    aiVertex += 2;
    mIB[aiTriangle++] = aiTriangleId++;
}

void CObjLoader::BuildMesh(FILE* aFile)
{
    rewind(aFile);

    int v[3] = { 0 };
    int vt[3] = { 0 };
    int vn[3] = { 0 };
    int lPositionIdx = 0;
    int lNormalIdx = 0;
    int lUVIdx = 0;
    int numVertices = 0;
    int numTexCoords = 0;
    int numNormals = 0;
    int activeMaterial = 0;
    char buffer[256] = { 0 };
    char vtx1[256] = { 0 };
    char vtx2[256] = { 0 };
    char vtx3[256] = { 0 };

    uint32 iVertex = 0;
    uint32 iVertexId = 0;
    uint32 iTriangle = 0;
    uint32 iTriangleId = 0;
    typedef std::map< std::string, uint32 > TIndicesMap;
    TIndicesMap lIndicesCache;
    CGeometrySPtr lGeometry;

    while (fscanf(aFile, "%s", buffer) != EOF)
    {
        switch (buffer[0])
        {
            case 'f': // v, v//vn, v/vt, or v/vt/vn.
                v[0] = v[1] = v[2] = 0;
                vt[0] = vt[1] = vt[2] = 0;
                vn[0] = vn[1] = vn[2] = 0;

                if (strstr(buffer, "//")) // v//vn
                {
                    sscanf(buffer, "%d//%d", &v[0], &vn[0]);
                    fscanf(aFile, "%d//%d", &v[1], &vn[1]);
                    fscanf(aFile, "%d//%d", &v[2], &vn[2]);

                    v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                    v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                    v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                    vn[0] = (vn[0] < 0) ? vn[0] + numNormals - 1 : vn[0] - 1;
                    vn[1] = (vn[1] < 0) ? vn[1] + numNormals - 1 : vn[1] - 1;
                    vn[2] = (vn[2] < 0) ? vn[2] + numNormals - 1 : vn[2] - 1;

                    //addTrianglePosNormal(numTriangles++, activeMaterial, v[0], v[1], v[2], vn[0], vn[1], vn[2]);

                    v[1] = v[2];
                    vn[1] = vn[2];

                    while (fscanf(aFile, "%d//%d", &v[2], &vn[2]) > 0)
                    {
                        v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;
                        vn[2] = (vn[2] < 0) ? vn[2] + numNormals - 1 : vn[2] - 1;

                        //addTrianglePosNormal(numTriangles++, activeMaterial, v[0], v[1], v[2], vn[0], vn[1], vn[2]);

                        v[1] = v[2];
                        vn[1] = vn[2];
                    }
                }
                else
                {
                    if( fscanf(aFile, "%s %s %s", vtx1, vtx2, vtx3) == 3  )
                    {
                        // v/vt/vn
                        sscanf(vtx1, "%d/%d/%d", &lPositionIdx, &lUVIdx, &lNormalIdx);

                        TIndicesMap::iterator lItfind = lIndicesCache.find(vtx1);

                        if (lItfind == lIndicesCache.end())
                        {
                            AddVertex(lPositionIdx, lNormalIdx, lUVIdx, iVertex, iTriangle, iTriangleId);
                            lIndicesCache[vtx1] = iVertexId++;
                        }
                        else
                        {
                            mIB[iTriangle++] = lItfind->second;
                        }

                        sscanf(vtx2, "%d/%d/%d", &lPositionIdx, &lUVIdx, &lNormalIdx);
                        lItfind = lIndicesCache.find(vtx2);

                        if (lItfind == lIndicesCache.end())
                        {
                            AddVertex(lPositionIdx, lNormalIdx, lUVIdx, iVertex, iTriangle, iTriangleId);
                            lIndicesCache[vtx2] = iVertexId++;
                        }
                        else
                        {
                            mIB[iTriangle++] = lItfind->second;
                        }

                        sscanf(vtx3, "%d/%d/%d", &lPositionIdx, &lUVIdx, &lNormalIdx);
                        lItfind = lIndicesCache.find(vtx3);

                        if (lItfind == lIndicesCache.end())
                        {
                            AddVertex(lPositionIdx, lNormalIdx, lUVIdx, iVertex, iTriangle, iTriangleId);
                            lIndicesCache[vtx3] = iVertexId++;
                        }
                        else
                        {
                            mIB[iTriangle++] = lItfind->second;
                        }
                    }
                    else if (sscanf(buffer, "%d/%d", &v[0], &vt[0]) == 2) // v/vt
                    {
                        fscanf(aFile, "%d/%d", &v[1], &vt[1]);
                        fscanf(aFile, "%d/%d", &v[2], &vt[2]);

                        v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                        v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                        v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                        vt[0] = (vt[0] < 0) ? vt[0] + numTexCoords - 1 : vt[0] - 1;
                        vt[1] = (vt[1] < 0) ? vt[1] + numTexCoords - 1 : vt[1] - 1;
                        vt[2] = (vt[2] < 0) ? vt[2] + numTexCoords - 1 : vt[2] - 1;

                        //addTrianglePosTexCoord(numTriangles++, activeMaterial, v[0], v[1], v[2], vt[0], vt[1], vt[2]);

                        v[1] = v[2];
                        vt[1] = vt[2];

                        while (fscanf(aFile, "%d/%d", &v[2], &vt[2]) > 0)
                        {
                            v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;
                            vt[2] = (vt[2] < 0) ? vt[2] + numTexCoords - 1 : vt[2] - 1;

                            //addTrianglePosTexCoord(numTriangles++, activeMaterial, v[0], v[1], v[2], vt[0], vt[1], vt[2]);

                            v[1] = v[2];
                            vt[1] = vt[2];
                        }
                    }
                    else // v
                    {
                        sscanf(buffer, "%d", &v[0]);
                        fscanf(aFile, "%d", &v[1]);
                        fscanf(aFile, "%d", &v[2]);

                        v[0] = (v[0] < 0) ? v[0] + numVertices - 1 : v[0] - 1;
                        v[1] = (v[1] < 0) ? v[1] + numVertices - 1 : v[1] - 1;
                        v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                        //addTrianglePos(numTriangles++, activeMaterial, v[0], v[1], v[2]);

                        v[1] = v[2];

                        while (fscanf(aFile, "%d", &v[2]) > 0)
                        {
                            v[2] = (v[2] < 0) ? v[2] + numVertices - 1 : v[2] - 1;

                            //addTrianglePos(numTriangles++, activeMaterial, v[0], v[1], v[2]);

                            v[1] = v[2];
                        }
                    }
                }

                break;

            case 'u': // usemtl
                fgets(buffer, sizeof(buffer), aFile);
                sscanf(buffer, "%s %s", buffer, buffer);
                activeMaterial = mMaterialsIds[buffer];
                break;

            case 'g': // group
                {
                    fgets(buffer, sizeof(buffer), aFile);
                    sscanf(buffer, "%s %s", buffer, buffer);

                    if (lGeometry)
                    {
                        lGeometry->Create(mFlags,
                                          &mVB[0],
                                          &mIB[0],
                                          numVertices,
                                          mIB.size());
                        mMesh->AddGeometry(activeMaterial, lGeometry);
                    }

                    lGeometry = CGeometrySPtr( new CGeometry() );
                }
                break;

            //*/
            case 'v': // v, vn, or vt.
                switch (buffer[1])
                {
                    case '\0': // v
                        fscanf(aFile, "%f %f %f",
                               &mPositions[numVertices][0],
                               &mPositions[numVertices][1],
                               &mPositions[numVertices][2]);
                        ++numVertices;
                        break;

                    case 'n': // vn
                        fscanf(aFile, "%f %f %f",
                               &mNormals[numNormals][0],
                               &mNormals[numNormals][1],
                               &mNormals[numNormals][2]);
                        ++numNormals;
                        break;

                    case 't': // vt
                        fscanf(aFile, "%f %f",
                               &mUVs[numTexCoords][0],
                               &mUVs[numTexCoords][1]);
                        ++numTexCoords;
                        break;

                    default:
                        break;
                }

                break;

            default:
                fgets(buffer, sizeof(buffer), aFile);
                break;
        }
    }

    // Add the last geometry
    if (lGeometry)
    {
        lGeometry->Create(mFlags,
                          &mVB[0],
                          &mIB[0],
                          iVertex / mVertexSize,
                          mIB.size());
        mMesh->AddGeometry(activeMaterial, lGeometry);
    }
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
                        lSubMaterial->SetRenderProperties(eRP_DiffuseMap);
                        mMaterialsIds[buffer] = lMaterialsCount;
                        ++lMaterialsCount;
                        break;

                    default:
                        fgets(buffer, sizeof(buffer), lFile);
                        break;
                }
            }

            mMaterial->SetSubMaterials( lSubMaterials );
        }
    }

    fclose(lFile);
}