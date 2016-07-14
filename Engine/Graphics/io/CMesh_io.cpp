#include "io/io.h"
#include "Logger/Logger.h"
#include "Mesh\Mesh.h"

#include <cstdio>

namespace io
{
	struct SObjVertex
	{
		float3 pos;
		float3 normal;
		float2 uv;
	};

    template <> bool Load(const CResource& aResource, CMesh& aObject)
    {
        bool lOk = false;

		std::FILE* lMeshFile = nullptr;
		fopen_s(&lMeshFile, aResource.GetFullFilename().c_str(), "rb");

        if(lMeshFile)
        {
			uint32 lFlags = 0;
			std::fread(&lFlags, sizeof(uint32), 1, lMeshFile);
			uint32 lNumMeshes = 0;
			std::fread(&lNumMeshes, sizeof(uint32), 1, lMeshFile);
			uint32 lMaterialIdx = 0;
			uint32 lVertexCount = 0;
			uint32 lFacesCount = 0;
			aObject.Resize(lNumMeshes);
			for (uint32 iMeshes = 0, lMeshesCount = lNumMeshes; iMeshes < lMeshesCount; ++iMeshes)
			{
				std::fread(&lMaterialIdx, sizeof(uint32), 1, lMeshFile);
				std::fread(&lVertexCount, sizeof(uint32), 1, lMeshFile);
				std::vector< SObjVertex > lGeometryData(lVertexCount);
				std::fread(&lGeometryData[0], sizeof(SObjVertex), lVertexCount, lMeshFile);

				std::fread(&lFacesCount, sizeof(uint32), 1, lMeshFile);
				lFacesCount *= 3;
				std::vector< uint32 > lIndices(lFacesCount);
				std::fread(&lIndices[0], sizeof(uint32), lFacesCount, lMeshFile);

				CGeometrySPtr lGeometry = std::make_shared< CGeometry >();
				lGeometry->Create(lFlags,
					&lGeometryData[0],
					&lIndices[0],
					lVertexCount,
					lFacesCount);

				aObject.AddGeometry(lMaterialIdx , lGeometry);
			}

			std::fclose(lMeshFile);
        }

        return 1;
    }
}