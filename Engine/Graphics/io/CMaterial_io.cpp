#include "io/io.h"
#include "Logger/Logger.h"
#include "Material/Material.h"
#include "Types.h"

#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>

#include "fbs/material_generated.h" // Already includes "flatbuffers/flatbuffers.h".

template <> bool Load( const CResource& aResource, CMaterial& aObject)
{
    bool lOk = false;
    uint8* lBufferPtr = nullptr;

    if (GetBufferPtr(aResource, lBufferPtr))
    {
		/*
        const Shader* lShader = GetShader(lBufferPtr);

        if (lShader)
        {
            CResource lShaderCode(lShader->filename()->c_str());

            aObject = CShaderSPtr(new CShader());

            ShaderType lShaderType;

            if(EnumString< ShaderType >::ToEnum( lShaderType, lShader->type()->c_str() ) )
            {
                if (aObject->Create(lShaderType, lShaderCode.GetFileContent().c_str()))
                {
                    lOk = true;
                }
            }
        }
		*/

        free(lBufferPtr);
    }

    if( !lOk )
    {
        //aObject = 0;
    }

    return lOk;
}