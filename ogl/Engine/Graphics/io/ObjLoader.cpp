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
CObjLoader::Load( const CResource& aResource )
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
		std::vector< CMesh > vMeshes;
		for each (tinyobj::shape_t shape in shapes)
		{
			CMesh mesh;
			//process_shape(shape);
		}
	}

	return false;
}