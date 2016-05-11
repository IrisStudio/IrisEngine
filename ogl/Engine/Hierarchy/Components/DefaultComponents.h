#ifndef __DEFAULT_COMPONENTS__
#define __DEFAULT_COMPONENTS__

#include "Types.h"

#include "Effect.h"
#include "EffectLibrary.h"
#include "ogl.h"
#include "Geometry.h"
#include "Mesh/Cube.h"
#include "Mesh/FullScreenQuad.h"

#include "io/Resource.h"

#include "io/ObjLoader.h"
#include "Material\Material.h"
#include "Material\SubMaterial.h"

struct Transform
{
    Transform(float3 position = float3(0.0f), float3 rotation = float3(0.0f), float3 scale = float3(0.0f))
        : position(position)
        , rotation(rotation)
        , scale(scale)
    {}

    float3 position, rotation, scale;
};

struct Velocity
{
    Velocity(float3 direction = float3(1.0f, 0.0f, 0.0f), float speed = 0.0f)
        : direction(direction)
        , speed(speed)
    {}

    float3 direction;
    float speed;
};

extern uint32 flags = 0;
struct Renderer
{
    Renderer( std::string aObj, RenderableProperties aMat )
    {
        mMesh = new CMesh;
        mMaterial = new CMaterial;
        CEffectLibrary::Instance().Init();
        CObjLoader lLoaderObj;
        lLoaderObj.Load(CResource( aObj ), mMesh);
        uint32 lCount = mMesh->GetGeometryCount();

        for (uint32 i = 0; i < lCount; ++i)
        {
            CSubMaterialSPtr lSubMaterial(new CSubMaterial(aMat));
            mMaterial->AddSubMaterial(lSubMaterial);
        }
    }

    ~Renderer()
    {
        CHECKED_DELETE(mMesh);
        CHECKED_DELETE(mMaterial);
    }

    CMesh* mMesh;
    CMaterial* mMaterial;
};

#endif //__DEFAULT_COMPONENTS__