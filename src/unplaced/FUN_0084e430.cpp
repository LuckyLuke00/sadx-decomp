#include "decls.h"
void Free(void *mp);
extern void *DAT_060d12b0;
extern int DAT_060d12ac;
void FUN_0084e4b0(int param_1);
void FUN_0084e430(int param_1);

// FUNCTION: SADX 0x0084e430
void FUN_0084e430(int param_1)
{
	void *var1 = DAT_060d12b0;
	while (var1 != 0)
	{
		void *var2 = *(void **)((char *)var1 + 0x18);
		void *var3 = *(void **)((char *)var1 + 0x1c);
		void *var4 = var3;
		if (var2 == 0)
		{
			DAT_060d12b0 = var3;
		}
		else
		{
			*(void **)((char *)var2 + 0x1c) = var3;
		}
		var3 = *(void **)((char *)var1 + 0x1c);
		if (var3 != 0)
		{
			*(void **)((char *)var3 + 0x18) = *(void **)((char *)var1 + 0x18);
		}
		Free(*(void **)((char *)var1 + 4));
		*(void **)((char *)var1 + 4) = 0;
		Free(*(void **)var1);
		*(void **)var1 = 0;
		Free(*(void **)((char *)var1 + 8));
		*(void **)((char *)var1 + 8) = 0;
		Free(var1);
		var1 = var4;
	}
	DAT_060d12b0 = 0;
	if (DAT_060d12ac == param_1)
	{
		DAT_060d12ac = 0;
	}
}

// FUNCTION: SADX 0x0084e780
void FUN_0084e780(int param_1)
{
	*(void (**)(int))(param_1 + 0x10) = FUN_0084e4b0;
	*(void (**)(int))(param_1 + 0x18) = FUN_0084e430;
}
