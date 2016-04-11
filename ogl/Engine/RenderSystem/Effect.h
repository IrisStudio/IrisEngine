#ifndef __EFFECT__
#define __EFFECT__

#include "Types.h"

#include "Shader.h"

#define IMPLEMENT_BIND_UNIFORM(TYPE)                                       \
    template <>                                                                     \
    void CEffect::BindFragment<TYPE>(const TYPE& in, const std::string& name)       \
    {                                                                               \
        ogl::CheckOGLError("After Bind uniform");                                   \
        const uint32 lFragmentShaderID = mFragmentShader->GetProgramID();           \
        GLint varLoc = ogl::glGetUniformLocation(lFragmentShaderID, name.c_str());  \
        BindUniform(lFragmentShaderID, varLoc, in);                                 \
        ogl::oglProgramUniform1i(lFragmentShaderID, 1, 0);                          \
        ogl::CheckOGLError("After Bind uniform");                                   \
    }                                                                               \
    template <>                                                                     \
    void CEffect::BindVertex<TYPE>(const TYPE& in, const std::string& name)         \
    {                                                                               \
        const uint32 lVertexShaderID = mVertexShader->GetProgramID();               \
        GLint varLoc = ogl::glGetUniformLocation(lVertexShaderID, name.c_str());    \
        BindUniform(lVertexShaderID, varLoc, in);                           \
    }                                                                               \

    class CEffect
    {
        public:
            CEffect( CShaderSPtr aVertexShader, CShaderSPtr aPixelShader);
            CEffect(const char* aVertexShader, const char* aPixelShader);
            virtual ~CEffect();
            void    Bind();
            uint32  GetID() const;
            void    BindMatrices(const float4x4& M, const float4x4& V, const float4x4& P);

            template <class T>
            void BindFragment(const T& in, const std::string& name);

            template <class T>
            void BindVertex(const T& in, const std::string& name);

            template <class T>
            void BindUniform(const uint32& Id, const int& varLoc, const T& in);

        private:
            uint32 mID;
            CShaderSPtr mVertexShader;
            CShaderSPtr mFragmentShader;
    };

    inline uint32 CEffect::GetID() const
    {
        return mID;
    }

    typedef std::shared_ptr< CEffect > CEffectSPtr;

#endif
