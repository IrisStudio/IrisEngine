#ifndef __IRIS_IO__
#define __IRIS_IO__

#include "Resource.h"
#include "Types.h"

template <typename T>             bool Save( CResource& aResource,       const T& aObject);
template <typename T, typename U> bool Save( const U* aIOObject,         const T& aObject);
template <typename T, typename U> bool Load( const U* aIOObject,         T& aObject);
template <typename T>             bool Load( const CResource& aResource, T& aObject);

bool GetBufferPtr(const CResource& aResource, uint8*& aBufferPtr );

#endif