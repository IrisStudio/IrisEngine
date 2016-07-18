#include "DrawQuadCmd.h"
#include "Mesh/FullScreenQuad.h"
#include "Material/Material.h"

namespace gph
{
    CDrawQuadCmd::CDrawQuadCmd(const std::string& aId)
        : CCommand( aId )
        , mMaterial( nullptr )
        , mQuad( std::make_shared< CFullScreenQuad >() )
    {
    }

    CDrawQuadCmd::~CDrawQuadCmd()
    {
    }

    void CDrawQuadCmd::Init(CMaterialSPtr aMaterial)
    {
        mMaterial = aMaterial;
        mQuad->Init(0, 0, 0);
    }
    void CDrawQuadCmd::Execute() const
    {
        mMaterial->Apply(0);
        mQuad->Render(0);
    }
}