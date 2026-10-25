#include "decls.h"

// FUNCTION: SADX 0x0069bd30
void FUN_0069bd30(struct task *param_1)
{
	if (param_1)
	{
		FUN_0069bd30((struct task *)param_1->awp);
		FUN_0069bd30((struct task *)param_1->thp);
		Free(param_1);
	}
}
