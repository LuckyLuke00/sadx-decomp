#include "decls.h"
extern float _nj_unit_matrix_[16];
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void late_ActionEx(struct NJS_ACTION *action, float frame, int flgs);
extern struct NJS_ACTION action_beamev_s_beam[1];
struct task;
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_shooting0;
extern struct NJS_ACTION action_shot_bf_s_bodya;
extern struct NJS_ACTION action_shot_s_ecfire;
void FUN_00422560(int param_1);
void ___njFogDisable();
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void FUN_004a88c0(NJS_ACTION *param_1, float param_2);
void late_ActionEx(NJS_ACTION *action, float frame, int flgs);
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
	late_ActionEx(&action_shot_s_ecfire, var1->counter.f, 4);
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
	late_ActionEx(&action_shot_s_ecfire, var1->counter.f, 4);
	njPopMatrix(1);
	LoadConstantAttr();
}

// STUB: SADX 0x007ee140
void FUN_007ee140(struct task *param_1)
{
}

// FUNCTION: SADX 0x007ee3d0
void ef_TameDisp(struct task *tp)
{
	struct taskwk *var1;
	struct task *var2;
	var1 = tp->twp;
	___njFogDisable();
	___njSetTexture(&texlist_shooting0);
	njPushMatrix(0);
	var2 = tp->ptp;
	njTranslateV(0, (struct NJS_POINT3 *)((char *)var2->twp + 0x20));
	FUN_0067d2d0(0, 0.5f, 0.5f, 0.5f);
	njTranslateV(0, &var1->pos);
	late_ActionEx((struct NJS_ACTION *)&action_beamev_s_beam, var1->value.f, 4);
	njPopMatrix(1);
}

// STUB: SADX 0x007ee450
void Hodai2Set(struct task *tp)
{
}

// FUNCTION: SADX 0x007ee720
void YarareMove(struct task *tp)
{
	struct taskwk *var1;
	struct taskwk *var2;
	struct NJS_POINT3 cpos;
	cpos.x = 0.0f;
	var1 = tp->twp;
	cpos.y = -324.0f;
	cpos.z = -1849.0f;
	var2 = tp->ptp->twp;
	njPushMatrix(&_nj_unit_matrix_);
	njTranslateV(0, &var2->pos);
	njRotateXYZ(0, var2->ang.x, var2->ang.y, var2->ang.z);
	njCalcPoint(0, &cpos, &var1->pos);
	njPopMatrix(1);
}
