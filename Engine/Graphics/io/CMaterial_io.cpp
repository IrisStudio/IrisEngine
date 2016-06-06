#include "io/io.h"
#include "Logger/Logger.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"
#include "Texture.h"
#include "Types.h"

#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>

#include "fbs/material_generated.h" // Already includes "flatbuffers/flatbuffers.h".

namespace io
{
    template <> bool Load(const CResource& aResource, CMaterial& aObject)
    {
        bool lOk = false;
        uint8* lBufferPtr = nullptr;

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
            }

            free(lBufferPtr);
        }

        if (!lOk)
        {
            //aObject = 0;
        }

        return lOk;
    }
}