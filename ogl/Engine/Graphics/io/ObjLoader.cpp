#include "ObjLoader.h"

#include "tiny_obj_loader.h"
#include "Mesh/Mesh.h"
#include "Logger/Logger.h"

namespace
{
}

CObjLoader::CObjLoader()
{
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

			assert(shape.mesh.positions.size());

			// Create the geometry of the object
			const uint32 nVertices = shape.mesh.positions.size() / 3;

			std::vector< float > lGeometryData( nVertices * 8, 0); // Positions + Normals + UV
			for (uint32 i8 = 0, i3 = 0, i2 = 0; i8 < nVertices* 8; i8 +=8, i3 +=3, i2 +=2 )
			{
				memcpy(&lGeometryData[i8], &shape.mesh.positions[i3], 3 * sizeof(float));
				memcpy(&lGeometryData[i8 + 3], &shape.mesh.normals[i3], 3 * sizeof(float));
				memcpy(&lGeometryData[i8 + 6], &shape.mesh.texcoords[i2], 2 * sizeof(float));
			}

			uint32 lFlags = eGD_Position;
			lFlags |= (shape.mesh.normals.size()) ? eGD_Normal : 0;
			lFlags |= (shape.mesh.texcoords.size()) ? eGD_UV : 0;

			lGeometry->Create( lFlags,
				               &lGeometryData[0],
				               &shape.mesh.indices[0],
							   nVertices,
							   shape.mesh.indices.size());
			aMesh.SetGeometry(lGeometry);
		}
	}

	return false;
}