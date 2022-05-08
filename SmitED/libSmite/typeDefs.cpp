#include "typeDefs.h"

sMaze::sMaze()
{
	memset(walldata, 0, 1024);
	memset(coldata, 0, 1024);
	memset(globalflags, 0, 128);
	memset(levelflags, 0, 128);
	script.clear();
	decompiledScript.clear();
}
