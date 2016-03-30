#ifndef _CGeometry_
#define _CGeometry_

#include <Types.h>

class CGeometry
{
    public:
        CGeometry();
        virtual ~CGeometry();
        void Create( const uint32 aFlags, void* aVertexBuffer, void* aIndexBuffer, uint32 aVertexCount, uint32 aIndexCount );
        void Bind() const;

    private: // Members
        uint32 mVAO;
        uint32 mVB;
        uint32 mIB;
    private: // Methods
};

typedef std::shared_ptr< CGeometry > CGeometrySPtr;

#endif
