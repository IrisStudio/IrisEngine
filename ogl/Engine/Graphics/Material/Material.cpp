#include "Material.h"
#include "SubMaterial.h"

CMaterial::CMaterial()
{

}

CMaterial::~CMaterial()
{

}

uint32 CMaterial::GetSubMaterialsCount() const
{
    return mSubMaterials.size();
}

void CMaterial::Apply(uint32 aIdx)
{
    mSubMaterials[aIdx]->Apply();
}

void CMaterial::AddSubMaterial(CSubMaterialSPtr aSubMaterial)
{
    mSubMaterials.push_back(aSubMaterial);
}