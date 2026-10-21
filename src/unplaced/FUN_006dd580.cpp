#include "decls.h"
extern int DAT_060bcea0;

// FUNCTION: SADX 0x006dd5e0
void FUN_006dd5e0(int param_1)
{
	DAT_060bcea0 = param_1;
}

// FUNCTION: SADX 0x006dd5f0
int FUN_006dd5f0()
{
	return DAT_060bcea0;
}
