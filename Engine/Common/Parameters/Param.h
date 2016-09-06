#ifndef __PARAM_H__
#define __PARAM_H__

#include "Named.h"

class CParam : public CNamed
{
    public:
		CParam() : CNamed() {}
		CParam( const std::string& aName ) : CNamed(aName) {}
        virtual ~CParam() {}
		const std::string& GetDescription() const { return mDescription; }
		void SetDescription(const std::string& aDescription ) { mDescription = aDescription;  }
    private:
		std::string mDescription;
};

template < class T >
class CTemplatedParam
{
public:
	CTemplatedParam() {}
	virtual ~CTemplatedParam() {}
	void		SetValue(const T& aValue) { mValue = aValue; }
	const T&	GetValue() const { return mValue; }
	void *		GetValueAddr(int index = 0) const { return ((void*)&m_Value + index); }
private:
	T mValue;
};

#endif // __PARAM_H__
