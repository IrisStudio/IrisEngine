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

            // We do not want data with out positions or normals
            assert(shape.mesh.positions.size());

            if (!shape.mesh.normals.size())
            {
                std::vector<float3> normals( (*std::max_element(shape.mesh.indices.begin(), shape.mesh.indices.end()))+1);

                for ( uint32 i = 0; i < shape.mesh.indices.size(); i+=3 )
                {
                    float3 v1(shape.mesh.positions[shape.mesh.indices[i]], shape.mesh.positions[shape.mesh.indices[i]] + 1, shape.mesh.positions[shape.mesh.indices[i]] + 2);
                    float3 v2(shape.mesh.positions[shape.mesh.indices[i + 1]], shape.mesh.positions[shape.mesh.indices[i + 1]] + 1, shape.mesh.positions[shape.mesh.indices[i + 1]] + 2);
                    float3 v3(shape.mesh.positions[shape.mesh.indices[i + 2]], shape.mesh.positions[shape.mesh.indices[i + 2]] + 1, shape.mesh.positions[shape.mesh.indices[i + 2]] + 2);

                    float3 v12 = v1 - v2;
                    float3 v13 = v1 - v3;

                    float3 normal = normalize( cross(v12, v13) );

                    normals[shape.mesh.indices[i]] = normal;
                    normals[shape.mesh.indices[i+1]] = normal;
                    normals[shape.mesh.indices[i+2]] = normal;
                }

                for (uint32 i = 0; i < normals.size(); ++i)
                {
                    shape.mesh.normals.push_back(normals[i].x);
                    shape.mesh.normals.push_back(normals[i].y);
                    shape.mesh.normals.push_back(normals[i].z);
                }
            }

            uint32 lFlags = eGD_Position;
            lFlags |= (shape.mesh.normals.size()) ? eGD_Normal : 0;
            lFlags |= (shape.mesh.texcoords.size()) ? eGD_UV : 0;

            // Create the geometry of the object
            const uint32 nVertices = shape.mesh.positions.size() / 3;

            std::vector< float > lGeometryData = mCopyFunctions[lFlags]( nVertices, shape.mesh );

            lGeometry->Create( lFlags,
                               &lGeometryData[0],
                               &shape.mesh.indices[0],
                               nVertices,
                               shape.mesh.indices.size());
            aMesh.AddGeometry(lGeometry);
        }
    }

    return false;
}