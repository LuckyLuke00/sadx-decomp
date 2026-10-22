#include "decls.h"
void FUN_005b30b0(struct taskwk *param_1, char *param_2);

// FUNCTION: SADX 0x0056d0b0
void FUN_0056d0b0(struct task *param_1, char *param_2)
{
	struct taskwk *local_8;
	if (param_1 != NULL)
	{
		local_8 = param_1->twp;
		FUN_005b30b0(local_8, param_2);
	}
}
