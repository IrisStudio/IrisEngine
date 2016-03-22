#ifndef _CGeometry_
#define _CGeometry_

#include <Types.h>

class CGeometry
{
    public:
        CGeometry();
        virtual ~CGeometry();
        template < uint32 N > void Create( void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexCount, uint32 aIndexCount );
        void Bind() const;

    private: // Members
        uint32 mVao;
        uint32 mVB;
    private: // Methods
};

typedef std::shared_ptr< CGeometry > CGeometrySPtr;

#endif
