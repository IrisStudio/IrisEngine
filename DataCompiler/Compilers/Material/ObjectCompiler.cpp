#include "ObjectCompiler.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "material_generated.h"

#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include "StringUtils.h"

#include "gph.h"

namespace
{
	void AddTextureToSubMaterial(aiMaterial *lSubMaterialPtr);
}


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

		flatbuffers::FlatBufferBuilder builder;

		std::vector<flatbuffers::Offset<SubMaterial>> lSubmaterials;
		
		for (size_t i = 0; i < scene->mNumMaterials; ++i)
		{
			aiMaterial *lSubMaterialPtr = scene->mMaterials[i];
			lSubMaterialPtr->Get(AI_MATKEY_NAME, lName);
			
			lSubmaterials.push_back( CreateSubMaterial(builder, builder.CreateString(lName.C_Str())) );
			
			printf("Name:%s/n", lName.C_Str());
			lSubMaterialPtr->Get(AI_MATKEY_COLOR_DIFFUSE, lAmbientColor);

			if (lSubMaterialPtr->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString Path;

				if (lSubMaterialPtr->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					std::string filename(Path.C_Str());
					OnlyFileName(filename, false);
					printf("Texture:%s/n", filename.c_str());
				}
			}
		}

		auto lSumbatersdafds = builder.CreateVector(lSubmaterials);
		auto lMaterial = CreateMaterial(builder, lSumbatersdafds);
		builder.Finish(lMaterial);

		std::ofstream myfile;
		myfile.open("C:/example.bin", std::ios::out | std::ios::app | std::ios::binary);
		myfile.write((char*)builder.GetBufferPointer(), builder.GetSize());
		myfile.close();
	}
}
