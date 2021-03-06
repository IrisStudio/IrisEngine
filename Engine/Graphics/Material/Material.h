#pragma once
#ifndef _CMaterial_
#define _CMaterial_

#include "gph.h"

class CMaterial
{
    public:
        typedef std::vector< CSubMaterialSPtr > TSubMaterials;
    public:
        CMaterial();
        virtual ~CMaterial();
        uint32  GetSubMaterialsCount() const;
        void    SetSubMaterials(TSubMaterials aSubMaterials);
        void    AddSubMaterial(CSubMaterialSPtr aSubMaterial);
        void    Apply( uint32 aIdx );

    protected:
        typedef std::vector< CSubMaterialSPtr > TSubMaterials;
        TSubMaterials  mSubMaterials;

    private:
        DISALLOW_COPY_AND_ASSIGN(CMaterial);
};

#endif