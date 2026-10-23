#include "decls.h"

// FUNCTION: SADX 0x0090a850
int __stdcall FUN_0090a850(int param_1, int param_2)
{
	return (~param_2) & param_1 & 1;
}

// FUNCTION: SADX 0x0090a860
int __stdcall FUN_0090a860(int param_1)
{
	if (param_1 >= 0xf && (param_1 & 1) == 0)
	{
		return 1;
	}
	return 0;
}
