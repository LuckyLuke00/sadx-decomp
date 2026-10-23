#include "decls.h"
#include <stdio.h>

// FUNCTION: SADX 0x009285c0
long __fastcall FUN_009285c0(FILE ***param_1)
{
	FILE **var1;
	long var2;
	long var3;

	var1 = *param_1;
	if (*var1 == NULL)
		return -1;

	var2 = ftell(*var1);
	fseek(*var1, 0, 2);
	var3 = ftell(*var1);
	fseek(*var1, var2, 0);
	return var3;
}
