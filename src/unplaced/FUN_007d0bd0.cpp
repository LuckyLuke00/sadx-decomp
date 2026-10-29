#include "decls.h"
extern int DAT_060cbfb4[10];

// FUNCTION: SADX 0x007d0bd0
int FUN_007d0bd0(void)
{
	int var1 = 0;
	while (var1 < 10)
	{
		if (DAT_060cbfb4[var1] == 0)
		{
			return var1;
		}
		var1++;
	}
	return -1;
}

// STUB: SADX 0x007d0bf0
void FUN_007d0bf0(struct task *param_1, struct task *param_2)
{
}
