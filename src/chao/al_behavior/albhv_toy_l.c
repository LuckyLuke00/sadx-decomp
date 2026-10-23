#include "decls.h"

// STUB: SADX 0x004699e0
long ALBHV_JumpFromHorse(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00469d60
long ALBHV_GoToTV(struct task *tp)
{
	struct task *var1;
	struct NJS_POINT3 pos;

	var1 = AL_GetFoundToyTask(tp);
	if (var1 != NULL)
	{
		if (ALO_GetTVWatchPos(&pos) != 0)
		{
			ALW_LockOn(tp, var1);
			MOV_SetAimPos(tp, &pos);
			AL_SetBehavior(tp, ALBHV_PostureChangeStand);
			AL_SetNextBehavior(tp, ALBHV_Notice);
			AL_SetNextBehavior(tp, ALBHV_GoToLockOn);
			AL_SetNextBehavior(tp, ALBHV_Touch);
			AL_SetNextBehavior(tp, ALBHV_GoToAim);
			AL_SetNextBehavior(tp, ALBHV_TurnToLockOn);
			AL_SetNextBehavior(tp, ALBHV_WatchTV);
			return 0;
		}
	}
	return 1;
}

// FUNCTION: SADX 0x00469e30
long ALBHV_GoToRadicase(struct task *tp)
{
	struct NJS_POINT3 pos;
	struct task *var1;

	var1 = AL_GetFoundToyTask(tp);
	if (var1 != 0)
	{
		if (ALO_GetRadicaseListenPos(&pos) != 0)
		{
			ALW_LockOn(tp, var1);
			MOV_SetAimPos(tp, &pos);
			AL_SetBehavior(tp, ALBHV_PostureChangeStand);
			AL_SetNextBehavior(tp, ALBHV_Notice);
			AL_SetNextBehavior(tp, ALBHV_GoToLockOn);
			AL_SetNextBehavior(tp, ALBHV_Touch);
			AL_SetNextBehavior(tp, ALBHV_GoToAim);
			AL_SetNextBehavior(tp, ALBHV_TurnToLockOn);
			AL_SetNextBehavior(tp, ALBHV_ListenRadicase);
			return 0;
		}
	}
	return 1;
}

// FUNCTION: SADX 0x00469f00
long ALBHV_GoToBall(struct task *tp)
{
	AL_GetFoundToyTask(tp);
	return 1;
}

// FUNCTION: SADX 0x00469f20
long ALBHV_GoToHorse(struct task *tp)
{
	struct task *var1;

	var1 = AL_GetFoundToyTask(tp);
	if (var1 != 0)
	{
		if (ALW_IsSheAttentionOtherOne(tp, var1) == 0)
		{
			MOV_SetAimPos(tp, &var1->twp->pos);
			ALW_CommunicationOn(tp, var1);
			AL_SetBehavior(tp, ALBHV_PostureChangeStand);
			AL_SetNextBehavior(tp, ALBHV_Notice);
			AL_SetNextBehavior(tp, ALBHV_GoToAim);
			AL_SetNextBehavior(tp, ALBHV_TurnToAim);
			AL_SetNextBehavior(tp, ALBHV_RideHorse);
			return 0;
		}
	}
	return 1;
}

// FUNCTION: SADX 0x00469fa0
long ALBHV_GoToBox(struct task *tp)
{
	struct task *var1;

	var1 = AL_GetFoundToyTask(tp);
	if (var1 != NULL)
	{
		ALW_LockOn(tp, var1);
		AL_SetBehavior(tp, ALBHV_PostureChangeStand);
		AL_SetNextBehavior(tp, ALBHV_Notice);
		AL_SetNextBehavior(tp, ALBHV_GoToLockOn);
		AL_SetNextBehavior(tp, ALBHV_Touch);
		AL_SetNextBehavior(tp, ALBHV_Think);
		return 0;
	}
	return 1;
}
