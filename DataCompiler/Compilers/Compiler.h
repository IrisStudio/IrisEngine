#pragma once
#ifndef _CCompiler_
#define _CCompilerr_

#include "Types.h"
#include "io\Resource.h"

class CCompiler
{
    public:
		CCompiler() {}
		virtual ~CCompiler() {}
		virtual void Compile(const CResource& aResource) = 0;

    private:
        DISALLOW_COPY_AND_ASSIGN(CCompiler);
};

#endif