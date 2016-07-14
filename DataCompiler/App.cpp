#include <stdio.h>

#include "Compilers\Material\ObjectCompiler.h"

int main(int argc, char **argv )
{
	CObjectCompiler lObjectCompiler;
	lObjectCompiler.Compile(CResource("models/dragon/chinesedragon.dae"));
  return 1;
}