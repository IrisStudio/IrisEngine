#include "ObjLoader.h"

#include "Logger/Logger.h"
#include "rs.h"

#include <algorithm>

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"
#include "Texture.h"

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
CObjLoader::Load( const CResource& aResource, CMesh* aMesh, CMaterial* aMaterial )
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    bool ret = tinyobj::LoadObj(shapes, materials, err, aResource.GetFullFilename().c_str(), aResource.GetDirectory().c_str(), tinyobj::calculate_normals | tinyobj::triangulation );

    if (!err.empty())   // `err` may contain warning message.
    {
        LOG_WARNING(err.c_str());
    }

    if (ret)
    {
        for each(tinyobj::material_t material in materials)
        {
            LOG_APPLICATION("material.name = %s\n", material.name.c_str());
            LOG_APPLICATION("  material.Ka = (%f, %f ,%f)\n", material.ambient[0], material.ambient[1], material.ambient[2]);
            LOG_APPLICATION("  material.Kd = (%f, %f ,%f)\n", material.diffuse[0], material.diffuse[1], material.diffuse[2]);
            LOG_APPLICATION("  material.Ks = (%f, %f ,%f)\n", material.specular[0], material.specular[1], material.specular[2]);
            LOG_APPLICATION("  material.Tr = (%f, %f ,%f)\n", material.transmittance[0], material.transmittance[1], material.transmittance[2]);
            LOG_APPLICATION("  material.Ke = (%f, %f ,%f)\n", material.emission[0], material.emission[1], material.emission[2]);
            LOG_APPLICATION("  material.Ns = %f\n", material.shininess);
            LOG_APPLICATION("  material.Ni = %f\n", material.ior);
            LOG_APPLICATION("  material.dissolve = %f\n", material.dissolve);
            LOG_APPLICATION("  material.illum = %d\n", material.illum);
            LOG_APPLICATION("  material.map_Ka = %s\n", material.ambient_texname.c_str());
            LOG_APPLICATION("  material.map_Kd = %s\n", material.diffuse_texname.c_str());
            LOG_APPLICATION("  material.map_Ks = %s\n", material.specular_texname.c_str());
            LOG_APPLICATION("  material.map_Ns = %s\n", material.bump_texname.c_str());

            CSubMaterialSPtr lSubMaterial(new CSubMaterial(eRP_DiffuseMap));
            CTextureSPtr lTexture(new CTexture());
			const size_t last_slash_idx = material.diffuse_texname.find_last_of("\\/");
			if (std::string::npos != last_slash_idx)
			{
				material.diffuse_texname.erase(0, last_slash_idx + 1);
			}

            lTexture->Create(eTT_2D, aResource.GetDirectory() + material.diffuse_texname);
            lSubMaterial->SetTexture(eTC_Diffuse, lTexture);
            aMaterial->AddSubMaterial(lSubMaterial);
        }

		const uint32 lSubMaterialsCount = aMaterial->GetSubMaterialsCount();
        aMesh->Resize(lSubMaterialsCount);

        for each (tinyobj::shape_t shape in shapes)
        {
            CGeometrySPtr lGeometry( new CGeometry() );

            // We do not want data without positions
            assert(shape.mesh.positions.size());
            assert(shape.mesh.normals.size());

            uint32 lFlags = eGD_Position;
            lFlags |= (shape.mesh.normals.size()) ? eGD_Normal : 0;
            lFlags |= (shape.mesh.texcoords.size()) ? eGD_UV : 0;

            // Create the geometry of the object
            const uint32 lVertices = shape.mesh.positions.size() / 3;

            std::vector< float > lGeometryData = mCopyFunctions[lFlags](lVertices, shape.mesh );

            lGeometry->Create( lFlags,
                               &lGeometryData[0],
                               &shape.mesh.indices[0],
                               lVertices,
                               shape.mesh.indices.size());

			LOG_APPLICATION("%u", shape.mesh.material_ids.front() );

            aMesh->AddGeometry(glm::clamp((int)(shape.mesh.material_ids.front()), 0, (int)lSubMaterialsCount), lGeometry);
        }
    }

    return false;
}