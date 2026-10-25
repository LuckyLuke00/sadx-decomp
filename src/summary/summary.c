#include "decls.h"
extern int DAT_05b360c8;
extern int DAT_05cd14d4;

// STUB: SADX 0x00494750
void calcvsyncsyoriochi()
{
}

// FUNCTION: SADX 0x004947b0
long SummaryExit(void *Param)
{
	npSetZCompareMode(1);
	DAT_05cd14d4 = 1;
	ADX_Close();
	GenocideTask();
	LoopTask();
	FUN_007d21b0((void *)1);
	DAT_05cd14d4 = 0;
	return 0;
}

// FUNCTION: SADX 0x00494950
void SummaryTaskDestructor(struct task *tp)
{
	struct anywk *var1 = tp->awp;
	if (var1 != 0)
	{
		if (*(int *)((char *)var1 + 0x28) != 0)
		{
			MSG_Close((struct MSGC *)var1);
		}
		if (*(void (**)(void))((char *)var1 + 0x17c) != 0)
		{
			(*(void (**)(void))((char *)var1 + 0x17c))();
		}
		Free(var1);
		tp->awp = 0;
	}
	DAT_05b360c8 |= 1;
}

// FUNCTION: SADX 0x00494b30
void SummaryBgmTask(struct task *tp)
{
	int iVar1;
	iVar1 = GetAdvertisePlayerNumber((unsigned char)GetPlayerNumber());
	if (iVar1 != -1)
	{
		BGM_Play(*(unsigned char *)(iVar1 + 0x2346a00));
	}
	FreeTask(tp);
}
