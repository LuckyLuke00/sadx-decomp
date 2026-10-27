#include "decls.h"
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);

// FUNCTION: SADX 0x0069bce0
void *FUN_0069bce0(void *param_1)
{
	void *var1 = 0;
	if (param_1)
	{
		var1 = MAlloc(0x34);
		memcpy(var1, param_1, 0x34);
		*(void **)((char *)var1 + 0x2c) = FUN_0069bce0(*(void **)((char *)param_1 + 0x2c));
		*(void **)((char *)var1 + 0x30) = FUN_0069bce0(*(void **)((char *)param_1 + 0x30));
	}
	return var1;
}

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
