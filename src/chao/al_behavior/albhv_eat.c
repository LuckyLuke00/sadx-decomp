#include "decls.h"
static long ALBHV_PickUpLockOn(struct task *tp);

// STUB: SADX 0x0045f7e0
static long ALBHV_PickUpLockOn(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0045f8d0
long ALBHV_GoToEat(struct task *tp)
{
	struct task *var1;

	var1 = AL_GetFoundFruitTask(tp);
	if (var1 != 0)
	{
		if (ALW_IsSheAttentionOtherOne(tp, var1) == 0)
		{
			ALW_LockOn(tp, var1);
			AL_SetBehavior(tp, ALBHV_PostureChangeStand);
			AL_SetNextBehavior(tp, ALBHV_Notice);
			AL_SetNextBehavior(tp, ALBHV_GoToLockOn);
			AL_SetNextBehavior(tp, ALBHV_PickUpLockOn);
			AL_SetNextBehavior(tp, ALBHV_Eat);
			return 0;
		}
	}
	return 1;
}

// FUNCTION: SADX 0x0045fb10
long AL_CheckFruit(struct task *tp)
{
	struct task *var1;
	long (*var2)(struct task *);

	var2 = (long (__cdecl *)(struct task *))AL_GetBehavior(tp);
	if (var2 == ALBHV_Eat || var2 == ALBHV_Sleep || var2 == ALBHV_TurnToFruit)
	{
		return 0;
	}
	var1 = CCL_IsHitKind2(tp->twp, 0x83);
	if (var1 != 0)
	{
		if (ALW_IsHeld(var1) == 0)
		{
			MOV_SetAimPos(tp, &var1->twp->pos);
			AL_SetBehavior(tp, ALBHV_TurnToFruit);
			return 1;
		}
	}
	return 0;
}
