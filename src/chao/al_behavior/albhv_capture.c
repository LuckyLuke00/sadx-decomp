#include "decls.h"

// STUB: SADX 0x0045e4e0
void FUN_0045e4e0(struct task *tp)
{
}

// STUB: SADX 0x0045e9f0
long ALBHV_TurnToMinimal(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0045ea80
long AL_CheckMinimal(struct task *tp)
{
	struct task *var1;
	long (*var2)(struct task *);

	var2 = (long (__cdecl *)(struct task *))AL_GetBehavior(tp);
	if (var2 == ALBHV_Capture || var2 == ALBHV_TurnToMinimal)
	{
		return 0;
	}
	var1 = CCL_IsHitKind2(tp->twp, 0x87);
	if (var1 != 0)
	{
		if (ALW_IsHeld(var1) == 0)
		{
			MOV_SetAimPos(tp, &var1->twp->pos);
			AL_SetBehavior(tp, ALBHV_TurnToMinimal);
			return 1;
		}
	}
	return 0;
}
