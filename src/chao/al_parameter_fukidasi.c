#include "decls.h"
extern struct task *DAT_05b314d8;

// FUNCTION: SADX 0x0045cac0
void ParamFukidasiDestructor(struct task *tp)
{
	if (DAT_05b314d8 == tp)
	{
		DAT_05b314d8 = 0;
	}
	if (tp->awp != 0)
	{
		syFree(tp->awp);
		tp->awp = 0;
	}
}

// FUNCTION: SADX 0x0045caf0
void AL_CloseParameterFukidasi(struct task *pChaoTask)
{
	if (DAT_05b314d8 != NULL)
	{
		struct OBJ_CONDITION *var1 = (struct OBJ_CONDITION *)DAT_05b314d8->awp;
		if ((*(int *)((char *)var1 + 0x38) == (int)pChaoTask) || (pChaoTask == NULL))
		{
			var1->scCount = 7;
			DAT_05b314d8 = NULL;
		}
	}
}

// FUNCTION: SADX 0x0045cb20
void AL_CloseParameterFukidasiWait(struct task *pChaoTask)
{
	struct anywk *var1;

	if (DAT_05b314d8 == 0)
	{
		return;
	}
	var1 = DAT_05b314d8->awp;
	if (*(struct task **)((char *)var1 + 0x38) != pChaoTask)
	{
		return;
	}
	*(unsigned char *)((char *)var1 + 0x0) = 6;
	*(int *)((char *)var1 + 0x4) = 0;
}

// STUB: SADX 0x0045cd00
void AL_OpenParameterFukidasiDakko(struct task *pChaoTask)
{
}
