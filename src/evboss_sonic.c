#include "decls.h"
void EvBossDispHitPoint(struct __HPPOS *hppos);
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

// STUB: SADX 0x005e0dc0
void EventBossCommonDisplayer(struct task *tp)
{
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

// FUNCTION: SADX 0x005e1d20
long CheckPlayer1Alive(struct task *tp)
{
	struct anywk *local_cg;
	struct task *local_8g;

	local_cg = tp->awp;
	local_8g = *(struct task **)((char *)local_cg + 0x54);
	if (local_8g == 0)
		return 0;
	if (*(char *)((char *)(*(void **)((char *)local_8g + 0x20)) + 1) == 0x32)
		return 0;
	return 1;
}

// FUNCTION: SADX 0x005e1d60
struct task *CreateBossPlayer(struct BOSSPLAYER_CREATE_PARAM *param)
{
	struct task *local_8;
	FUN_005e1e10(1);
	param->exec = NULL;
	switch (param->type)
	{
		case 0:
		case 1:
			local_8 = EventBossSonicSet(param);
			break;
		case 2:
		case 3:
			local_8 = EventBossKnucklesSet(param);
			break;
		case 4:
		case 5:
			local_8 = EventBossE102Set(param);
			break;
		default:
			local_8 = NULL;
			break;
	}
	if (local_8 != NULL)
	{
		SetRingForPlayerBossStage(local_8, param);
	}
	return local_8;
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

// STUB: SADX 0x005e2330
void SetPosForPlayerBossStage(struct task *tp)
{
}

// FUNCTION: SADX 0x005e2420
struct task *CreateBossPlayerTask(struct BOSSPLAYER_CREATE_PARAM *Param)
{
	struct task *local_8;
	local_8 = NULL;
	if (Param == NULL)
	{
		return NULL;
	}
	switch (Param->type)
	{
		case 0:
		case 1:
			local_8 = CreateElementalTask(7, 1, SonicTheHedgehog);
			*(char *)((char *)local_8->twp + 9) = 0;
			*(char *)((char *)local_8->twp + 8) = 1;
			break;
		case 2:
		case 3:
			local_8 = CreateElementalTask(7, 1, KnucklesTheEchidna);
			*(char *)((char *)local_8->twp + 9) = 3;
			*(char *)((char *)local_8->twp + 8) = 1;
			break;
		case 4:
		case 5:
			local_8 = CreateElementalTask(7, 1, E102);
			*(char *)((char *)local_8->twp + 9) = 6;
			*(char *)((char *)local_8->twp + 8) = 1;
			break;
	}
	Param->boss_tp = local_8;
	return local_8;
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

// STUB: SADX 0x005e2570
void EvBossMakeCrashBothCollisionedPlayersP(unsigned char pno0, unsigned char pno1, float scalor)
{
}

// STUB: SADX 0x005e2660
float ghUnitVectorXZ(const struct NJS_POINT3 *r4, struct NJS_POINT3 *r5)
{
	return (float)0;
}

// STUB: SADX 0x005e26d0
long EvBossCheckColliThrough(struct EVBOSS_WORK *bwk)
{
	return (long)0;
}

// FUNCTION: SADX 0x005e27e0
void EvBossDispHitPoint(struct __HPPOS *hppos)
{
	ghInitPvrTexture();
	___njSetTexture(&texlist_score);
	FUN_007d21b0((void *)1);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	ghDrawPvrTexture(*(int *)((char *)hppos + 0xc), *(float *)((char *)hppos + 0x0) * ScreenRaitoX, *(float *)((char *)hppos + 0x4) * ScreenRaitoY, *(float *)((char *)hppos + 0x8));
}
