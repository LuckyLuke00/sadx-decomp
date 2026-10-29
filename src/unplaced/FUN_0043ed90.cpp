#include "decls.h"
extern char DAT_05aeb6a0[2][0xc820];

// FUNCTION: SADX 0x0043ed90
int FUN_0043ed90(void)
{
	return (int)DAT_05aeb6a0[ALMC_GetSystemSlot()];
}
