#include <stdio.h>

#include "Compilers\Material\ObjectCompiler.h"

int main(int argc, char **argv )
{
	CObjectCompiler lObjectCompiler;
	lObjectCompiler.Compile(CResource("models/head/head.obj"));
  return 1;
}