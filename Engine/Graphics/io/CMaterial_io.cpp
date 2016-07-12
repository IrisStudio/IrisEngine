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

        std::ifstream lMaterialFile( aResource.GetFullFilename() );

        if( lMaterialFile.is_open() )
        {
            std::stringstream strStream;
            strStream << lMaterialFile.rdbuf();//read the file
            auto j = json::parse(strStream.str());

            LOG_APPLICATION("%s", j.dump().c_str());

            json::iterator lItSubMaterials = j.find("submaterials");

            if (lItSubMaterials != j.end() )
            {
                for (json::iterator it = lItSubMaterials->begin(); it != lItSubMaterials->end(); ++it)
                {
                    json::iterator lItDiffColor;

                    if( ( lItDiffColor =  it->find("diffuse_color") ) != it->end() )
                    {
                        lItDiffColor->find("r").value();
                        lItDiffColor->find("g").value();
                        lItDiffColor->find("b").value();
                    }
                }
            }
        }

        /*
        if (GetBufferPtr(aResource, lBufferPtr))
        {

        auto lMaterial = GetMaterial(lBufferPtr);

        auto lSubmaterials = lMaterial->submaterials();

        for (unsigned int i = 0; i < lSubmaterials->size(); i++)
        {
        CSubMaterialSPtr lSubmaterial( new CSubMaterial() );
        lSubmaterial->mAmbientColor  = *lSubmaterials->Get(i)->ambient();
        lSubmaterial->mDiffuseColor  = *lSubmaterials->Get(i)->diffuse();
        lSubmaterial->mSpecularColor = *lSubmaterials->Get(i)->specular();
        lSubmaterial->mTransmittance = *lSubmaterials->Get(i)->transmittance();
        lSubmaterial->mTransparency  = lSubmaterials->Get(i)->transparent();

        const flatbuffers::String* lDiffuseMap = lSubmaterials->Get(i)->diffuse_map();

        if( strcmp( lDiffuseMap->c_str(), "") == 0 )
        {
        CTextureSPtr lTexture(new CTexture());
        lTexture->Create(eTT_2D, aResource.GetDirectory() + lDiffuseMap->str() );
        lSubmaterial->mTextures[eTC_Diffuse] = lTexture;
        }
        }*/


        return 1;
    }
}