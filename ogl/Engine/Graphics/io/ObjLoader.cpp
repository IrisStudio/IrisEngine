#include "ObjLoader.h"

#include "Mesh/Mesh.h"
#include "Logger/Logger.h"
#include "rs.h"

#include <algorithm>

namespace
{
}

CObjLoader::CObjLoader()
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
CObjLoader::Load( const CResource& aResource, CMesh& aMesh )
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    bool ret = tinyobj::LoadObj(shapes, materials, err, aResource.GetFullFilename().c_str());

    if (!err.empty())   // `err` may contain warning message.
    {
        LOG_WARNING(err.c_str());
    }

    if (ret)
    {
        for each (tinyobj::shape_t shape in shapes)
        {
            CGeometrySPtr lGeometry( new CGeometry() );

            // We do not want data without positions
            assert(shape.mesh.positions.size());

            const uint32 lIndexCount = shape.mesh.indices.size();

            const std::vector< float >& lVerticesVector = shape.mesh.positions;
            std::vector< float >& lNormals = shape.mesh.normals;

            //if (!shape.mesh.normals.size())
            {
                // The size of the normals must be the same size as the vertices, because we want one normal for each vertex
                lNormals.resize(lVerticesVector.size());

                const std::vector< uint32 >& lIndicesVector = shape.mesh.indices;

                for ( register uint32 i = 0; i < lIndexCount; i+=3 )
                {
                    float3 v1, v2, v3;
                    memcpy(&v1, &lVerticesVector[lIndicesVector[i] * 3], sizeof(float3));
                    memcpy(&v2, &lVerticesVector[lIndicesVector[i + 1] * 3], sizeof(float3));
                    memcpy(&v3, &lVerticesVector[lIndicesVector[i + 2] * 3], sizeof(float3));

                    float3 v12 = v1 - v2;
                    float3 v13 = v1 - v3;

                    float3 normal = normalize( cross(v12, v13) );

                    memcpy(&lNormals[lIndicesVector[i] * 3], &normal, sizeof(float3));
                    memcpy(&lNormals[lIndicesVector[i + 1] * 3], &normal, sizeof(float3));
                    memcpy(&lNormals[lIndicesVector[i + 2] * 3], &normal, sizeof(float3));
                }
            }

            uint32 lFlags = eGD_Position;
            lFlags |= (shape.mesh.normals.size()) ? eGD_Normal : 0;
            lFlags |= (shape.mesh.texcoords.size()) ? eGD_UV : 0;

            // Create the geometry of the object
            const uint32 lVertices = lVerticesVector.size() / 3;

            std::vector< float > lGeometryData = mCopyFunctions[lFlags](lVertices, shape.mesh );

            lGeometry->Create( lFlags,
                               &lGeometryData[0],
                               &shape.mesh.indices[0],
                               lVertices,
                               lIndexCount);
            aMesh.AddGeometry(lGeometry);
        }
    }

    return false;
}