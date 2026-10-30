#include "decls.h"

// FUNCTION: SADX 0x004951c0
unsigned long FUN_004951c0(unsigned long param_1, unsigned long param_2)
{
	unsigned long var1 = (unsigned long)((unsigned char)param_1 * (unsigned char)param_2 / 255) |
		(unsigned long)((unsigned char)((param_1 >> 8) & 0xff) * (unsigned char)((param_2 >> 8) & 0xff) / 255) << 8 |
		(unsigned long)((unsigned char)((param_1 >> 16) & 0xff) * (unsigned char)((param_2 >> 16) & 0xff) / 255) << 16 |
		(unsigned long)((unsigned char)((param_1 >> 24) & 0xff) * (unsigned char)((param_2 >> 24) & 0xff) / 255) << 24;
	return var1;
}
