#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include <vector>
#include "TemplatedVectorMap.h"

class CParam;
class CParameters : public CTemplatedVectorMap< CParam* >
{
public:
	CParameters() {}
	virtual ~CParameters() {}
private:
};

#endif // __PARAMETERS_H__
