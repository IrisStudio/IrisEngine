#include "io/io.h"
#include "Logger/Logger.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"
#include "Texture.h"
#include "Types.h"

#include <iostream>
#include <fstream>

#include "io/json.h"
using json = nlohmann::json;

#define FETCH(name) (it->)

namespace io
{
	template <> bool Load(const CResource& aResource, CMaterial& aObject)
	{
		bool lOk = false;

		std::ifstream lMaterialFile(aResource.GetFullFilename());

		if (lMaterialFile.is_open())
		{
			std::stringstream strStream;
			strStream << lMaterialFile.rdbuf();//read the file
			auto j = json::parse(strStream.str());

			LOG_APPLICATION("%s", j.dump().c_str());

			json::iterator lItSubMaterials = j.find("submaterials");
			size_t size = lItSubMaterials->size();

			if (lItSubMaterials != j.end())
			{
				for (json::iterator it = lItSubMaterials->begin(); it != lItSubMaterials->end(); ++it)
				{
					CSubMaterialSPtr lSubmaterial = std::make_shared<CSubMaterial>();
					json::iterator itFind;
					if ((itFind = it->find("diffuse_color")) != it->end())
						lSubmaterial->mDiffuseColor = float3(itFind->find("r")->get<float>(), itFind->find("g")->get<float>(), itFind->find("b")->get<float>());

					if ((itFind = it->find("diffuse_map")) != it->end())
					{
						CTextureSPtr lTexture(new CTexture());
						lTexture->Create(eTT_2D, aResource.GetDirectory() + itFind->get<std::string>() );
						lSubmaterial->mTextures[eTC_Diffuse] = lTexture;
					}
					
					lSubmaterial->SetRenderProperties(eRP_DiffuseMap);
					aObject.AddSubMaterial(lSubmaterial);
				}
			}

			lOk = true;
		}

		return lOk;
	}
}