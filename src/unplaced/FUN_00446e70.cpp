#include "decls.h"
extern int DAT_0095c0a0[256];

// FUNCTION: SADX 0x00446e70
unsigned long FUN_00446e70(unsigned char *param_1, long param_2, unsigned long param_3, unsigned long param_4)
{
	while (param_2 != 0)
	{
		param_3 = (param_3 >> 8) ^ DAT_0095c0a0[(param_3 & 0xff) ^ *param_1];
		param_1++;
		param_2--;
	}
	return param_3 ^ param_4;
}
