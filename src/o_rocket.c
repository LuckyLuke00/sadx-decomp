#include "decls.h"
extern struct NJS_MODEL *DAT_05a86a68;
extern struct NJS_MODEL DAT_05a86ed4;
extern "C" int rand(void);
extern void ObjectRocketH_Fade(struct task *tp);
void FUN_005b8590(struct taskwk *param_1, struct motionwk *param_2);
void FUN_005b93c0(struct task *param_1);
void FUN_005b9490(struct task *param_1);
extern const struct CCL_INFO rocket_colli_info[1];
extern int DAT_05edc104[10];

// STUB: SADX 0x005b76c0
void FUN_005b76c0(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2)
{
}

// STUB: SADX 0x005b7730
void ObjectRocketBaseHS(struct task *tp)
{
}

// STUB: SADX 0x005b78e0
void ObjectRocketBaseV(struct task *tp)
{
}

// FUNCTION: SADX 0x005b7c20
void ClrRocketTaskWorkBuff()
{
	int *local_cg;
	int local_8g;
	local_cg = &DAT_05edc104[0];
	for (local_8g = 0; local_8g < 10; local_8g++)
	{
		*local_cg = 0;
		local_cg++;
	}
}

// STUB: SADX 0x005b7c60
void InitRocketBase_H(struct task *tp)
{
}

// FUNCTION: SADX 0x005b7e00
void InitRocketBase_V(struct task *tp)
{
	struct taskwk *local_8g;
	struct obj *local_cg;

	local_8g = tp->twp;
	local_8g->counter.ptr = &DAT_05a86ed4;
	tp->disp = DrawRocketBase;
	tp->dest = DstrRocketBase;
	local_8g->mode = 1;
	local_8g->smode = local_8g->ang.x & 0xf;
	local_8g->ang.x = 0;
	local_cg = EntryMobileLandCollsion(tp, DAT_05a86a68);
	if (local_cg != 0)
	{
		local_8g->timer.l = (long)local_cg;
		SetMobileLandCollsionData(local_8g, local_cg);
	}
}

// FUNCTION: SADX 0x005b8040
int FUN_005b8040(int param_1)
{
	int *local_cg;
	int local_8g;

	local_cg = &DAT_05edc104[0];
	for (local_8g = 0; local_8g < 10; local_8g++)
	{
		if (*local_cg == 0)
		{
			*local_cg = param_1;
			*(char *)(param_1 + 1) = local_8g;
			return 1;
		}
		local_cg++;
	}
	return 0;
}

// STUB: SADX 0x005b82c0
void FUN_005b82c0(int param_1)
{
}

// STUB: SADX 0x005b8300
void FUN_005b8300(int param_1)
{
}

// FUNCTION: SADX 0x005b8350
void FUN_005b8350(int param_1)
{
	int *local_8;

	local_8 = *(int **)((char *)param_1 + 0x20);
	*(char *)local_8 = 1;
	*(float *)(local_8 + 4) = 0.0f;
}

// STUB: SADX 0x005b8370
void DrawRocketBase(struct task *tp)
{
}

// FUNCTION: SADX 0x005b8410
void DstrRocketBase(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	WithdrawCollisionEntry(tp, *(struct obj **)((char *)local_8 + 0xc));
	ReleaseMobileLandObject(*(struct obj **)((char *)local_8 + 0xc));
}

// STUB: SADX 0x005b8450
void FUN_005b8450(struct task *tp)
{
}

// FUNCTION: SADX 0x005b8520
void ObjectRocket_Wait(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	struct forcewk *local_cg = tp->fwp;

	local_8g->mode = 1;
	tp->disp = FUN_005b93c0;
	tp->dest = FUN_005b9490;
	local_cg->pos_spd.x = local_8g->pos.x;
	local_cg->pos_spd.y = local_8g->pos.y;
	local_cg->pos_spd.z = local_8g->pos.z;
	CCL_Init(tp, (struct CCL_INFO *)&rocket_colli_info, 1, 4);
}

// STUB: SADX 0x005b8590
void FUN_005b8590(struct taskwk *twp, struct motionwk *mwp)
{
}

// STUB: SADX 0x005b8900
void ObjectRocket_Move_Pl(struct task *tp)
{
}

// FUNCTION: SADX 0x005b8ae0
void ObjectRocket_Change(struct task *tp)
{
	void (*local_8)(struct task *);
	Rocket_Open(tp);
	local_8 = tp->disp;
	local_8(tp);
}

// STUB: SADX 0x005b8c90
void ObjectRocket_Move(struct task *tp)
{
}

// STUB: SADX 0x005b8d40
void Rocket_Hold_H(struct task *tp)
{
}

// STUB: SADX 0x005b8e40
void ObjectRocketH_Fade(struct task *tp)
{
}

// STUB: SADX 0x005b8ec0
void Rocket_Hold_V(struct task *tp)
{
}

// STUB: SADX 0x005b8ff0
void ObjectRocketV_Fade(struct task *tp)
{
}

// STUB: SADX 0x005b9060
void ObjectRocketV_Dead(struct task *tp)
{
}

// STUB: SADX 0x005b94c0
void DrawRocketJet(struct task *tp)
{
}

// STUB: SADX 0x005b96b0
void SetRocketSmoke(struct task *tp)
{
}

// FUNCTION: SADX 0x005b97e0
void CreateRocketSmoke(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_rocketsmoke.link;
	local_ci = SpCreateTask(local_8gk, EffectSmoke);
	if (local_ci != NULL)
	{
		local_ci->pos = *pos;
		local_ci->spd = *velo;
		local_ci->scl = scl * 0.15f;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 6.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 360.0) * 65536.0 / 360.0);
		local_ci->argb.a = 1.0;
		local_ci->argb.r = 1.0;
		local_ci->argb.g = 1.0;
		local_ci->argb.b = 1.0;
		local_ci->work[0].ptr = &default_rocketsmoke;
	}
}
