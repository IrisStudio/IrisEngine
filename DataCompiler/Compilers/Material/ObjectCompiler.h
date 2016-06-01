#pragma once
#ifndef _CObjectCompiler_
#define _CObjectCompiler_

#include "Compilers\Compiler.h"

class CObjectCompiler : public CCompiler
{
    public:
		CObjectCompiler();
        virtual ~CObjectCompiler();
		virtual void Compile(const CResource& aResource);

    private:
        DISALLOW_COPY_AND_ASSIGN(CObjectCompiler);
};

#endif