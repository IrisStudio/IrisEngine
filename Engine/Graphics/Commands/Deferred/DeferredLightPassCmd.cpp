#include "DeferredLightPassCmd.h"
#include "Effect.h"
#include "io/Resource.h"
#include "Mesh/FullScreenQuad.h"
#include "Material/Material.h"
#include "Material/SubMaterial.h"

namespace gph
{
    CDeferredLightPassCmd::CDeferredLightPassCmd()
        : CDrawQuadCmd( "CDeferredLightPassCmd" )
    {
    }

    CDeferredLightPassCmd::~CDeferredLightPassCmd()
    {

    }
    void CDeferredLightPassCmd::Init()
    {
        CMaterialSPtr lMaterial = std::make_shared< CMaterial >();
        CSubMaterialSPtr lSubMaterial = std::make_shared< CSubMaterial >();
        CEffect* lDefferedLightPassEffect = new CEffect(CResource("shaders/deferred/light_pass.vs").GetFileContent().c_str(), CResource("shaders/deferred/light_pass.fs").GetFileContent().c_str());
        lSubMaterial->SetEffect(lDefferedLightPassEffect);
        lMaterial->AddSubMaterial(lSubMaterial);
        CDrawQuadCmd::Init(lMaterial);
    }
    void CDeferredLightPassCmd::Execute() const
    {
        CDrawQuadCmd::Execute();
    }
}