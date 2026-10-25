#include "decls.h"
struct task;
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_shooting0;
extern struct NJS_ACTION action_shot_bf_s_bodya;
extern struct NJS_ACTION action_shot_s_ecfire;
void FUN_00422560(int param_1);
void ___njFogDisable();
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void njPushMatrix(float *param_1);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void njRotateXYZ(long param_1, long param_2, long param_3, long param_4);
void FUN_004a88c0(NJS_ACTION *param_1, float param_2);
void FUN_004a8a50(NJS_ACTION *param_1, float param_2, int param_3);
void njPopMatrix(int param_1);
void npSetZCompare();

// FUNCTION: SADX 0x007ede30
void EggDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	FUN_00422560(3);
	___njFogDisable();
	___njSetTexture(&texlist_shooting0);
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	FUN_004a88c0(&action_shot_bf_s_bodya, var1->value.f);
	FUN_004a8a50(&action_shot_s_ecfire, *(float *)&var1->counter.f, 4);
	njPopMatrix(1);
	npSetZCompare();
}

// STUB: SADX 0x007eded0
void EggEngine(struct task *tp)
{
}

// FUNCTION: SADX 0x007edf50
void EggDisp2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njFogDisable();
	SaveConstantAttr();
	if (*(signed char *)((char *)var1 + 0xd) > 0)
	{
		OnConstantAttr(0, 0x100000);
		SetMaterial(1.0, 1.0, 1.0, 1.0);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
	___njSetTexture(&texlist_shooting0);
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	FUN_0067d2d0(0, 0.5, 0.5, 0.5);
	FUN_004a88c0(&action_shot_bf_s_bodya, var1->value.f);
	FUN_004a8a50(&action_shot_s_ecfire, var1->counter.f, 4);
	njPopMatrix(1);
	LoadConstantAttr();
}

// STUB: SADX 0x007ee140
void FUN_007ee140(struct task *cTask)
{
}

// STUB: SADX 0x007ee450
void Hodai2Set(struct task *tp)
{
}

// STUB: SADX 0x007ee720
void YarareMove(struct task *tp)
{
}
