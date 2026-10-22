#include "decls.h"

// FUNCTION: SADX 0x005b30b0
void FUN_005b30b0(struct taskwk *param_1, char *param_2)
{
	char *local_8;

	local_8 = (char *)param_1->ewp + 0x5c;
	*(char **)(local_8 + 8) = param_2;
	if (*(short *)(local_8 + 2) == 0)
	{
		*(short *)(local_8 + 4) = 0;
		*(short *)(local_8 + 2) = 1;
		*(char *)(local_8 + 0) = 0;
		*(char *)(local_8 + 1) = 0;
	}
	return;
}
