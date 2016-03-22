#ifndef _CGeometry_
#define _CGeometry_

#include <Types.h>

class CGeometry
{
    public:
        CGeometry();
        virtual ~CGeometry();
        void Create( uint32 aFlags, void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexCount, uint32 aIndexCount );
        void Bind() const;

    private: // Members
        uint32 mVao;
        uint32 mVB;
    private: // Methods
        template < typename T > void FillBufferData(void* aVertexBuffer, uint32 aVertexCount);
};

#endif
