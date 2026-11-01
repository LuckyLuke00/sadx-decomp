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

// FUNCTION: SADX 0x007d0bf0
void FUN_007d0bf0(struct task *param_1, struct task *param_2)
{
	int var1;
	struct task *var2;
	struct taskwk *var3;
	struct task *var4;

	for (var1 = 0; var1 < 10; var1++)
	{
		var2 = (struct task *)DAT_060cbfb4[var1];
		if (var2 != 0)
		{
			var3 = var2->twp;
			if (var3 != 0)
			{
				var4 = (struct task *)var3->value.ptr;
			}
			if (var4 != 0)
			{
				if (var4->next == param_1)
				{
					DestroyTask(var2);
					DAT_060cbfb4[var1] = 0;
				}
			}
		}
	}
}
