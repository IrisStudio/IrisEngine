#include "EffectLibrary.h"

#include "XML/XML.h"
#include "io/io.h"
#include "Shader.h"
#include "Effect.h"
#include "Logger/Logger.h"

#include <string>

CEffectLibrary::CEffectLibrary()
{
}

CEffectLibrary::~CEffectLibrary()
{
}

CEffectSPtr CEffectLibrary::CreateEffect(const char* aEffectFile)
{
    CShaderSPtr lVertexShader;
    iris::io::Load(iris::io::CResource("shaders/effect01.bin"), lVertexShader);


    /*
    CEffectSPtr lEffect;
    CShaderSPtr lVertexShader;
    CShaderSPtr lPixelShader;
    xml::CDocument lDocument;

    if (xml::OpenDocument(lDocument, aEffectFile))
    {
        std::hash<std::string> hash_fn;
        xml::CNode lEffectNode = lDocument.child("effect");

        for (xml::CNode lShaderNode = lEffectNode.first_child(); lShaderNode; lShaderNode = lShaderNode.next_sibling())
        {
            const std::string& lTag  = lShaderNode.name();
            const std::string& lFile = xml::GetAttribute<std::string>(lShaderNode, "file");
            uint32 str_hash = hash_fn(lFile);

            if (lTag == "vertex_shader")
            {
                if( iris::io::Load( lFile, lVertexShader ) )
                {
                    mVertexShaderLibrary[str_hash] = lVertexShader;
                }
            }
            else if (lTag == "pixel_shader")
            {
                if (iris::io::Load(lFile, lPixelShader))
                {
                    mPixelShaderLibrary[str_hash] = lPixelShader;
                }
            }
        }
    }

    if (lVertexShader && lPixelShader)
    {
        lEffect = CEffectSPtr( new CEffect( lVertexShader, lPixelShader ) );
    }

    return lEffect;
    */

    return CEffectSPtr();
}
