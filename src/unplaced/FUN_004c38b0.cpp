#include "decls.h"

extern unsigned char DAT_05b92ec8[768];
extern unsigned char DAT_05b92e54;

// FUNCTION: SADX 0x004c38b0
int FUN_004c38b0(int param_1)
{
	return DAT_05b92ec8[param_1 * 3];
}

// FUNCTION: SADX 0x004c38d0
int FUN_004c38d0()
{
	return DAT_05b92e54;
}
