#ifndef _iris_io_
#define _iris_io_


namespace iris { namespace io
{
	template <typename T, typename U> bool Serialize	( U* aIOObject,			const T& aObject);
	template <typename T> bool Serialize	( CResource& aResource, const T& aObject);
	template <typename T, typename U> bool Unserialize(U* aIOObject, const T& aObject);
	template <typename T> bool Unserialize	( const CResource& aResource, T& aObject);
}}

#endif