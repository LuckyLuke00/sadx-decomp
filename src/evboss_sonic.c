#include "decls.h"
extern int DAT_05edd2d8;

// FUNCTION: SADX 0x005e0d40
void EventBossCommonDestructor(struct task *tp)
{
	struct anywk *local_8 = tp->awp;
	if (*(struct task **)((char *)local_8 + 0x68))
	{
		FreeTask(*(struct task **)((char *)local_8 + 0x68));
		*(struct task **)((char *)local_8 + 0x68) = NULL;
	}
	if (*(struct task **)((char *)local_8 + 0x6c))
	{
		FreeTask(*(struct task **)((char *)local_8 + 0x6c));
		*(struct task **)((char *)local_8 + 0x6c) = NULL;
	}
	FUN_005e1e10(0);
	if (*(void (**)(struct task *))((char *)local_8 + 0x14))
	{
		(*(void (**)(struct task *))((char *)local_8 + 0x14))(tp);
	}
}

// FUNCTION: SADX 0x005e0e70
void EventBossSonicDestructor(struct task *tp)
{
	struct anywk *local_8;
	local_8 = tp->awp;
	if (*(struct task **)((char *)local_8 + 0x64))
	{
		DestroyTask(*(struct task **)((char *)local_8 + 0x64));
	}
	EventBossCommonDestructor(tp);
}

// STUB: SADX 0x005e1d20
long CheckPlayer1Alive(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x005e1e10
void FUN_005e1e10(int param_1)
{
	DAT_05edd2d8 = param_1;
}

// STUB: SADX 0x005e22b0
void PlayerBossRingTask(struct task *tp)
{
}

// FUNCTION: SADX 0x005e2500
void FreeBossPlayerTask(struct BOSSPLAYER_CREATE_PARAM *Param)
{
	struct task *local_8;
	if (Param != NULL)
	{
		if (Param->boss_tp != NULL)
		{
			Param->boss_tp->exec = FreeTask;
			Param->boss_tp->disp = NULL;
			Param->boss_tp = NULL;
		}
	}
	else
	{
		local_8 = GetPlayerTaskPointer(1);
		if (local_8 != NULL)
		{
			local_8->exec = FreeTask;
			local_8->disp = NULL;
		}
	}
}

// STUB: SADX 0x005e2660
float ghUnitVectorXZ(const struct NJS_POINT3 *r4, struct NJS_POINT3 *r5)
{
	return (float)0;
}
