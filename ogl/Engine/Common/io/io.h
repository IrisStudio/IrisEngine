#ifndef _iris_io_
#define _iris_io_


namespace iris { namespace io
{
	template <typename T> bool Serialize(const T& aObject);
	template <typename T> bool Unserialize(T& aObject);
}}

#endif