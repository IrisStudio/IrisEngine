#include "io/io.h"
#include "Logger/Logger.h"
#include "Shader.h"
#include "Types.h"


#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>

#include "fbs/shader_generated.h" // Already includes "flatbuffers/flatbuffers.h".

namespace iris
{
    namespace io
    {
        template <> bool Load( const CResource& aResource, CShaderSPtr& aObject)
        {
            bool lOk = false;
            uint8* lBufferPtr = nullptr;

            if (GetBufferPtr(aResource, lBufferPtr))
            {
                const Shader* lShader = GetShader(lBufferPtr);

                if (lShader)
                {
                    const char* lName = lShader->name()->c_str();
                    CResource lShaderCode(lShader->filename()->c_str());
                    aObject = CShaderSPtr(new CShader());

                    if (aObject->Create(CShader::VERTEX_SHADER, lShaderCode.GetFileContent().c_str()))
                    {
                        lOk = true;
                    }

                }

                free(lBufferPtr);
            }

            if( !lOk )
            {
                aObject = 0;
            }

            return lOk;
        }
    }
}