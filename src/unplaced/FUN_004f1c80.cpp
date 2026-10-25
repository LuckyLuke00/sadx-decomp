#include "decls.h"
extern int DAT_05baf388[8];

// FUNCTION: SADX 0x004f1c80
int FUN_004f1c80(int param_1)
{
	int local_cg;
	int local_8g;
	local_cg = -1;
	if (param_1 == 0)
	{
		return local_cg;
	}
	for (local_8g = 0; local_8g < 8; local_8g++)
	{
		if (DAT_05baf388[local_8g] == param_1)
		{
			local_cg = *(unsigned char *)((char *)(*(int *)(param_1 + 0x20)) + 9);
			break;
		}
	}
	return local_cg;
}
