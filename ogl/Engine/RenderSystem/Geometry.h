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
        inline uint32 GetFlags() const;

    private: // Members
        uint32 mVAO;
        uint32 mVB;
        uint32 mIB;
        uint32 mVertexCount;
        uint32 mIndexCount;
        uint32 mFlags;

    private: // Methods
};

inline uint32 CGeometry::GetFlags() const
{
    return mFlags;
}

typedef std::shared_ptr< CGeometry > CGeometrySPtr;

#endif
