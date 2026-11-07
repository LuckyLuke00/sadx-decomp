#include "decls.h"

#include <stdlib.h>
struct colliwk;
extern struct NJS_ACTION action_sorsar_karada_1[1];
extern struct particle_info robo_smoke1;
float EnemyDist2FromPlayer(struct taskwk *twp, int num);
long AdjustAngle(long ang0, long ang1, long dang);
void RoboBumpSide(struct taskwk *twp, struct enemywk *ewp);
void FUN_005536c0(struct particle_info *param_1);
void FUN_005be2d0(struct taskwk *, struct enemywk *);
void EnemyCheckGroundCollision(struct taskwk *twp, struct enemywk *ewp);
long EnemyCalcPlayerAngle(struct taskwk *twp, struct enemywk *ewp, unsigned char pnum);
void RoboDraw(struct taskwk *twp, struct enemywk *ewp);
void FUN_005be2d0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_POINT3 DAT_0264dbac;
extern struct NJS_POINT3 DAT_0264dbb8;
void RoboHeadChase(struct task *tp, struct enemywk *ewp);
void FUN_005bc3f0(struct task *param_1, struct enemywk *param_2);
void RoboHeadTakeOff(struct task *tp, struct enemywk *ewp);
void RoboHeadWait(struct task *tp, struct enemywk *ewp);
void RoboHeadReturn(struct task *tp, struct enemywk *ewp);
void ___njSetTexture(struct NJS_TEXLIST *texlist);
int dsCheckViewV(struct NJS_POINT3 *ft, float radius);
void ___dsSetPalette(long no);
void ResetMaterial();
void SaveControl3D();
void SetMaterial(float a, float r, float g, float b);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void late_DrawModel(struct NJS_MODEL *mdl, int flgs);
void LoadControl3D();
extern struct NJS_TEXLIST texlist_e_robo;
extern struct NJS_MODEL model_sorsar_karada_1_atama1[];
extern void RoboHeadDisplayer(struct task *tp);
extern struct taskwk *DAT_05baf368[8];
void FUN_005be280(int param_1, int param_2);
void FUN_005be2d0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005bf2c0(struct taskwk *param_1, void *param_2);
void FUN_005bf0d0(void *param_1, void *param_2);
void FUN_005bf870(int param_1, int param_2);
void RoboSmokeGround(struct taskwk *twp, struct enemywk *ewp);
extern struct NJS_SPRITE sprite_robo_beam;
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// STUB: SADX 0x005bbf00
void EnemyRoboHead(struct task *tp)
{
}

// FUNCTION: SADX 0x005bc0c0
void RoboHeadDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	RoboHeadDraw(local_cg, local_8g);
}

// FUNCTION: SADX 0x005bc0f0
void RoboHeadDraw(struct taskwk *twp, struct enemywk *ewp)
{
	___njSetTexture(&texlist_e_robo);
	if (dsCheckViewV(&twp->pos, 20.0f) == 0)
	{
		return;
	}
	___dsSetPalette(6);
	ResetMaterial();
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njPushMatrix(0);
	njUnitMatrix(0);
	FUN_0067d830(0, twp->pos.x, twp->pos.y, twp->pos.z);
	UNKNOWN_ROTATE_Y_MACRO(0, twp->ang.y);
	UNKNOWN_ROTATE_Y_MACRO(0, 0x4000);
	FUN_0067d2d0(0, 1.5f, 1.5f, 1.5f);
	njGetMatrix((NJS_MATRIX (*))&ewp->mat[0]);
	njPopMatrix(1);
	njPushMatrix(0);
	njMultiMatrix(0, (NJS_MATRIX (*))&ewp->mat[0]);
	late_DrawModel((struct NJS_MODEL *)&model_sorsar_karada_1_atama1, 1);
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
	___dsSetPalette(0);
}

// STUB: SADX 0x005bc260
void RoboHeadExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x005bc3f0
void FUN_005bc3f0(struct task *param_1, struct enemywk *param_2)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	if (param_1->ptp->twp->mode == 3)
	{
		param_2->old_mode = local_8->mode;
		local_8->mode = 1;
		local_8->wtimer = 0;
		local_8->pos = param_1->ptp->twp->pos;
		local_8->ang.y = ((struct enemywk *)param_1->ptp->mwp)->sub_angle[4];
	}
}

// FUNCTION: SADX 0x005bc470
void RoboHeadTakeOff(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	local_8g = ewp->shadow.hit[2].onpos;
	if (local_cg->wtimer < 0x14)
	{
		RoboHeadSmokeSide(local_cg, ewp);
		local_cg->pos.y += 0.05f;
	}
	else
	{
		if (local_8g + 30.0f > local_cg->pos.y)
		{
			local_cg->pos.y += 0.12f;
			RoboHeadSmokeUnder(local_cg, ewp);
		}
		else
		{
			ewp->old_mode = local_cg->mode;
			local_cg->mode = 2;
			local_cg->wtimer = 0;
			local_cg->cwp->flag &= ~0x1;
			ewp->force.y = local_cg->pos.y;
		}
	}
	EnemyCheckGroundCollision(local_cg, ewp);
	RoboHeadDraw(local_cg, ewp);
}

// FUNCTION: SADX 0x005bc560
void RoboHeadSmokeSide(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 local_3c;
	struct NJS_POINT3 local_30g;
	struct NJS_POINT3 local_24g;
	struct NJS_POINT3 local_18;
	int local_8g;
	local_30g.x = 5.0f;
	local_30g.y = 1.5f;
	local_30g.z = 0.0f;
	local_24g.x = 0.7f;
	local_24g.y = -0.05f;
	local_24g.z = 0.0f;
	njPushMatrix(0);
	njUnitMatrix(0);
	njSetMatrix(0, (NJS_MATRIX *)((char *)ewp + 0x1fc));
	for (local_8g = 0; local_8g < 8; local_8g++)
	{
		njPushMatrix(0);
		UNKNOWN_ROTATE_Y_MACRO(0, local_8g << 0xd);
		njCalcVector(0, &local_24g, &local_18);
		njCalcPoint(0, &local_30g, &local_3c);
		FUN_005536c0(&robo_smoke1);
		robo_smoke1.velo = local_18;
		robo_smoke1.pos = local_3c;
		njPopMatrix(1);
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005bc6a0
void RoboHeadSmokeUnder(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 pos;
	struct NJS_POINT3 tpos;
	struct NJS_POINT3 tmp_velo;
	struct NJS_POINT3 velo;
	tpos.x = 0.0f;
	tpos.y = 1.0f;
	tpos.z = 0.0f;
	tmp_velo.x = 0.0f;
	tmp_velo.y = -0.5f;
	tmp_velo.z = 0.0f;
	njPushMatrix(0);
	njUnitMatrix(0);
	njSetMatrix(0, &ewp->mat);
	njCalcVector(0, &tmp_velo, &velo);
	njCalcPoint(0, &tpos, &pos);
	njPopMatrix(1);
	robo_smoke2.velo = velo;
	robo_smoke2.pos = pos;
	FUN_005536c0(&robo_smoke2);
}

// FUNCTION: SADX 0x005bc780
void RoboHeadChase(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;
	local_cg = tp->twp;
	local_8g = DAT_05baf368[0];
	ewp->aim = local_8g->pos;
	FUN_005e3d10(local_cg, ewp);
	ewp->acc.x = njCos(local_cg->ang.y) * ewp->force.x;
	ewp->acc.z = njSin(-local_cg->ang.y) * ewp->force.x;
	RoboHeadUp(local_cg, ewp);
	FUN_005bc940(local_cg, ewp);
	EnemyCheckGroundCollision(local_cg, ewp);
	RoboHeadDraw(local_cg, ewp);
	if (RoboHeadCaptureBeam(tp, ewp) != 0)
	{
		ewp->old_mode = local_cg->mode;
		local_cg->mode = 3;
		local_cg->wtimer = 0;
		tp->ptp->twp->flag |= 0x200;
		local_cg->flag |= 0x8000;
		SetInputP(local_cg->cwp->hit_cwp->mytask->twp->counter.b[0], 0x21);
	}
	if (local_cg->wtimer > 0x12c)
	{
		ewp->old_mode = local_cg->mode;
		local_cg->mode = 3;
		local_cg->wtimer = 0;
		tp->ptp->twp->flag |= 0x200;
	}
	if (local_cg->wtimer > 0x3c)
	{
		EntryColliList(local_cg);
	}
	else
	{
		local_cg->cwp->flag &= ~0x1;
	}
}

// FUNCTION: SADX 0x005bc940
void FUN_005bc940(void *param_1, void *param_2)
{
	*(float *)((char *)param_2 + 0x10) = -*(float *)((char *)param_2 + 4) * 0.03999999910593033 + *(float *)((char *)param_2 + 0x10);
	*(float *)((char *)param_2 + 0x14) = -*(float *)((char *)param_2 + 8) * 0.03999999910593033 + *(float *)((char *)param_2 + 0x14);
	*(float *)((char *)param_2 + 0x18) = -*(float *)((char *)param_2 + 0xc) * 0.03999999910593033 + *(float *)((char *)param_2 + 0x18);
	*(float *)((char *)param_2 + 4) = *(float *)((char *)param_2 + 4) + *(float *)((char *)param_2 + 0x10);
	*(float *)((char *)param_2 + 0xc) = *(float *)((char *)param_2 + 0xc) + *(float *)((char *)param_2 + 0x18);
	*(float *)((char *)param_1 + 0x20) = *(float *)((char *)param_1 + 0x20) + *(float *)((char *)param_2 + 4);
	*(float *)((char *)param_1 + 0x28) = *(float *)((char *)param_1 + 0x28) + *(float *)((char *)param_2 + 0xc);
	*(float *)((char *)param_2 + 0x10) = 0.0f;
	*(float *)((char *)param_2 + 0x14) = 0.0f;
	*(float *)((char *)param_2 + 0x18) = 0.0f;
}

// STUB: SADX 0x005bca00
long RoboHeadCaptureBeam(struct task *tp, struct enemywk *ewp)
{
	return (long)0;
}

// STUB: SADX 0x005bcb70
void EffectRoboBeam(struct task *tp)
{
}

// STUB: SADX 0x005bcd10
void RoboBeamDisplayer(struct task *tp)
{
}

// STUB: SADX 0x005bce00
void EffectRoboBeam2(struct task *tp)
{
}

// STUB: SADX 0x005bcfb0
void RoboBeam2Displayer(struct task *tp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	local_8g = local_cg->scl.x;
	if (dsCheckViewV(&local_cg->pos, 10.0f) == 0)
	{
		return;
	}
	SetMaterial(local_cg->scl.z, 0.4f, 0.4f, 1.0f);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 10);
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	UNKNOWN_ROTATE_X_MACRO(0, 0xc000);
	FUN_0067d2d0(0, local_8g, local_8g, local_8g);
	late_DrawSprite3D(&sprite_robo_beam, 0, 0x22, 4);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005bd0b0
void RoboHeadUp(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;
	local_8 = ewp->shadow.hit[2].onpos;
	if (EnemyDist2FromPlayer(twp, 0) < 900.0f && (DAT_05baf368[0]->flag & 0x8000) == 0)
	{
		twp->pos.y += 1.2f;
		if (twp->pos.y > ewp->force.y + 20.0f)
		{
			twp->pos.y = ewp->force.y + 20.0f;
		}
	}
	else
	{
		twp->pos.y -= 0.5f;
		if (twp->pos.y < local_8 + 30.0f)
		{
			twp->pos.y = local_8 + 30.0f;
		}
	}
}

// FUNCTION: SADX 0x005bd170
void RoboHeadWait(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;

	local_cg = tp->twp;
	local_8g = DAT_05baf368[0];
	local_cg->ang.y -= 0x400;
	ewp->acc.x -= ewp->velo.x * 0.05f;
	ewp->acc.z -= ewp->velo.z * 0.05f;
	RoboHeadUp(local_cg, ewp);
	FUN_005bc940(local_cg, ewp);
	EnemyCheckGroundCollision(local_cg, ewp);
	RoboHeadDraw(local_cg, ewp);
	if (tp->ptp->twp->mode == 7)
	{
		ewp->old_mode = local_cg->mode;
		local_cg->mode = 4;
		local_cg->wtimer = 0;
		ewp->aim = tp->ptp->twp->pos;
	}
	EntryColliList(local_cg);
}

// FUNCTION: SADX 0x005bd270
void RoboHeadReturn(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	local_8g = (ewp->aim.x - local_cg->pos.x) * (ewp->aim.x - local_cg->pos.x)
		+ (ewp->aim.z - local_cg->pos.z) * (ewp->aim.z - local_cg->pos.z);
	ewp->aim = tp->ptp->twp->pos;
	RoboHeadUp(local_cg, ewp);
	FUN_005e3d10(local_cg, ewp);
	FUN_005bc940(local_cg, ewp);
	EnemyCheckGroundCollision(local_cg, ewp);
	RoboHeadDraw(local_cg, ewp);
	if (local_8g < 100.0f)
	{
		ewp->old_mode = local_cg->mode;
		local_cg->mode = 5;
		local_cg->wtimer = 0;
		ewp->aim_angle = ((struct enemywk *)tp->ptp->mwp)->sub_angle[4];
	}
	else if (local_8g < 400.0f)
	{
		ewp->acc.x = njCos(local_cg->ang.y) * ewp->force.x * 0.2f;
		ewp->acc.z = njSin(-local_cg->ang.y) * ewp->force.x * 0.2f;
	}
	else
	{
		ewp->acc.x = njCos(local_cg->ang.y) * ewp->force.x * 0.4f;
		ewp->acc.z = njSin(-local_cg->ang.y) * ewp->force.x * 0.4f;
	}
}

// FUNCTION: SADX 0x005bd410
void RoboHeadDocking(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_18;
	struct taskwk *local_cj;
	float local_14;
	float local_10;
	float local_8g;

	local_18 = tp->twp;
	local_cj = tp->ptp->twp;
	local_18->ang.y = AdjustAngle(local_18->ang.y,
		((struct enemywk *)tp->ptp->mwp)->sub_angle[4], 0x200);
	local_14 = local_cj->pos.x - local_18->pos.x;
	local_10 = local_cj->pos.y + ((struct enemywk *)tp->ptp->mwp)->force.y - local_18->pos.y;
	local_8g = local_cj->pos.z - local_18->pos.z;
	if (local_14 > 0.0f)
	{
		local_18->pos.x += 0.1f;
	}
	else
	{
		local_18->pos.x -= 0.1f;
	}
	if (local_10 > 0.0f)
	{
		local_18->pos.y += 0.07f;
	}
	else if (local_10 > -1.0f)
	{
		local_18->pos.y -= 0.03f;
		RoboHeadSmokeSide(local_18, ewp);
	}
	else
	{
		local_18->pos.y -= 0.07f;
	}
	if (local_8g > 0.0f)
	{
		local_18->pos.z += 0.1f;
	}
	else
	{
		local_18->pos.z -= 0.1f;
	}
	if (local_14 * local_14 + local_10 * local_10 + local_8g * local_8g < 0.25f)
	{
		ewp->old_mode = local_18->mode;
		local_18->mode = 0;
		local_18->wtimer = 0;
		tp->ptp->twp->flag |= 0x100;
		dsPlay_timer_v(0x36a, (int)local_18, 1, 0, 1,
			local_18->pos.x, local_18->pos.y, local_18->pos.z);
	}
	EnemyCheckGroundCollision(local_18, ewp);
	RoboHeadDraw(local_18, ewp);
}

// STUB: SADX 0x005bd920
void RoboDestructor(struct task *tp)
{
}

// STUB: SADX 0x005bd990
void RoboExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x005bdc30
void FUN_005bdc30(struct taskwk *param_1, struct enemywk *param_2)
{
	struct taskwk *local_ci;
	short local_18;
	unsigned short local_14;
	struct colliwk *local_10;
	struct colliwk *local_8g;

	local_ci = DAT_05baf368[0];
	local_18 = (unsigned short)local_ci->flag;
	local_14 = (unsigned short)param_1->cwp->hit_num;
	local_10 = param_1->cwp;
	local_8g = param_1->cwp->hit_cwp;
	if (EnemyCheckDamage(param_1, param_2) != 0)
	{
		*(char *)param_1 = 0xa;
		param_1->counter.b[1] = 0;
		param_1->counter.b[2] = 1;
		param_1->scl.z = 0.35f;
	}
}

// FUNCTION: SADX 0x005bdcb0
void RoboEditMode(struct taskwk *twp)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___dsSetPalette(6);
	___njSetTexture(&texlist_e_robo);
	if (0.0f <= twp->scl.x)
	{
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		UNKNOWN_ROTATE_Y_MACRO(0, twp->ang.y + 0x4000);
		UNKNOWN_ROTATE_X_MACRO(0, 0x2000);
		FUN_0067d2d0(0, 1.2f, 1.2f, 1.2f);
		FUN_004a88c0((struct NJS_ACTION *)&action_sorsar_karada_1, 1.0f);
		njPopMatrix(1);
	}
	else
	{
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		UNKNOWN_ROTATE_Y_MACRO(0, twp->ang.y + 0x4000);
		FUN_0067d2d0(0, 1.2f, 1.2f, 1.2f);
		FUN_004a88c0((struct NJS_ACTION *)&action_sorsar_karada_1, 1.0f);
		njPopMatrix(1);
	}
	___dsSetPalette(0);
}

// FUNCTION: SADX 0x005bde30
void FUN_005bde30(struct task *param_1, struct OBJ_CONDITION *param_2, void *param_3)
{
	struct taskwk *local_cg;
	void *local_8g;
	local_cg = (struct taskwk *)param_2->unionStatus.pObjSleepCondition;
	local_8g = local_cg->value.ptr;
	if (local_8g != 0)
	{
		Free(local_8g);
	}
	Free(local_cg);
	param_2->unionStatus.pObjSleepCondition = 0;
	FUN_005b5aa0(param_1, param_2, param_3);
	DeadOut(param_1);
}

// FUNCTION: SADX 0x005bdea0
void FUN_005bdea0(struct taskwk *param_1, int param_2)
{
	CreateFlash2(param_1->pos.x, param_1->pos.y + 5.0f, param_1->pos.z, 1.4f);
	CreateExpSpring(param_1, 8);
	CreateAnimal(8, param_1->pos.x, param_1->pos.y + 15.0f, param_1->pos.z);
}

// FUNCTION: SADX 0x005bdf30
void RoboSwing(struct taskwk *twp, struct enemywk *ewp)
{
	struct colliwk *local_8g;
	float local_cg;

	local_cg = EnemyDist2FromPlayer(twp, 0);
	local_8g = twp->cwp;
	ewp->aim = DAT_05baf368[0]->pos;
	EnemyCalcAimAngle(twp, ewp);
	twp->ang.y = AdjustAngle(twp->ang.y, ewp->aim_angle, 0x900);
	if ((local_8g->flag & 1) && local_8g->my_num == 1 && local_8g->hit_cwp->id == 0)
	{
		RoboBumpSide(twp, ewp);
	}
	switch (twp->smode)
	{
	case 0:
		ewp->angz_spd += 0x800;
		break;
	case 1:
		twp->cwp->info[1].attr &= ~0x10;
		ewp->nframe += 0.45f;
		if (ewp->nframe > 29.0f)
		{
			ewp->nframe = 29.0f;
			twp->smode = 2;
			ewp->lframe = ewp->pframe;
		}
		twp->flag &= ~0x2000;
		break;
	case 2:
		twp->cwp->info[1].attr &= ~0x10;
		if (twp->wtimer > 20)
		{
			twp->smode = 3;
		}
		twp->flag &= ~0x2000;
		break;
	case 3:
		twp->cwp->info[1].attr |= 0x10;
		ewp->angz_spd -= 0x800;
		twp->flag |= 0x2000;
		break;
	case 4:
		twp->flag &= ~0x2800;
		twp->mode = ewp->old_mode;
		twp->wtimer = 0;
		break;
	}
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
}

// STUB: SADX 0x005be1b0
void RoboBumpSide(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005be720
void RoboSleep(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg;
	float local_8g;
	local_cg = tp->twp;
	if (RoboHearSound(local_cg, ewp))
	{
		ewp->old_mode = local_cg->mode;
		local_cg->mode = 1;
		local_cg->wtimer = 0;
	}
	FUN_005be280((int)local_cg, (int)ewp);
	FUN_005be2d0(local_cg, ewp);
	if (local_cg->flag & 0x1000)
	{
		ewp->sub_angle[1] -= 0x44;
		if (((ewp->sub_angle[1] + 0x8000) & 0xffff) < 0x6600)
		{
			local_cg->flag &= ~0x1000;
			ewp->sub_angle[1] = -0x1a00;
			ewp->sub_angle[3] = 0x8000;
		}
		local_8g = 0.0f;
		ewp->nframe -= 0.12f;
		if (ewp->nframe < 0.5f)
		{
			ewp->nframe = 0.5f;
		}
	}
	else
	{
		local_8g = njSin(ewp->sub_angle[3]);
		ewp->sub_angle[1] = (long)(local_8g * 8.0f * 65536.0f / 360.0f) - 0x1a00;
		ewp->nframe = (1.0f + local_8g) * 0.5f;
	}
	ewp->sub_angle[3] += 0x180;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	ewp->force.z = 1.9f;
	ewp->sub_angle[0] += 0x130;
	ewp->sub_angle[4] = AdjustAngle(ewp->sub_angle[4], local_cg->ang.y, 0x80);
	EnemyCheckGroundCollision(local_cg, ewp);
	RoboDraw(local_cg, ewp);
}

// FUNCTION: SADX 0x005be930
long RoboHearSound(struct taskwk *twp, struct enemywk *ewp)
{
	struct taskwk *local_8g;
	struct playerwk *local_cg;
	local_8g = DAT_05baf368[0];
	local_cg = (struct playerwk *)((struct motionwk *)DAT_05ba3328[0])->work.ptr;
	if (EnemyDist2FromPlayer(twp, 0) < 22500.0f)
	{
		if (PCheckJump(local_8g, local_cg) || local_cg->spd.x >= local_cg->p.jog_speed * 1.8f)
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x005be9b0
void RoboWakeUp(struct taskwk *twp, struct enemywk *ewp)
{
	unsigned short local_8;
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	ewp->sub_angle[1] = AdjustAngle(ewp->sub_angle[1], 0, 0xb0);
	if (ewp->force.z < 2.1f)
	{
		ewp->force.z += 0.05f;
	}
	ewp->sub_angle[0] += 0x190;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	if (ewp->nframe < 9.0f)
	{
		ewp->nframe += 0.22f;
	}
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
	local_8 = (unsigned short)(twp->wtimer % 0x32);
	if ((local_8 == 0) || (local_8 == 0x11))
	{
		twp->btimer = 0;
	}
	if (twp->btimer++ < 0xa)
	{
		RoboSmokeSide(twp, ewp);
	}
	RoboSmokeUnder(twp, ewp);
	if (twp->wtimer > 0x28)
	{
		ewp->sub_angle[6] = 0x4000;
		ewp->old_mode = twp->mode;
		twp->mode = 2;
		twp->wtimer = 0;
		ewp->sub_angle[5] = 0x1a0;
		ewp->sub_angle[2] = 0x70;
	}
}

// STUB: SADX 0x005beb60
void RoboSmokeSide(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005beca0
void RoboSmokeUnder(struct taskwk *twp, struct enemywk *ewp)
{
	struct NJS_POINT3 pos;
	struct NJS_POINT3 tpos;
	struct NJS_POINT3 tmp_velo;
	struct NJS_POINT3 velo;
	tpos.x = 0.0f;
	tpos.y = -4.3f;
	tpos.z = 0.0f;
	tmp_velo.x = 0.0f;
	tmp_velo.y = -0.7f;
	tmp_velo.z = 0.0f;
	njPushMatrix(0);
	njUnitMatrix(0);
	njSetMatrix(0, &ewp->mat);
	njCalcVector(0, &tmp_velo, &velo);
	njCalcPoint(0, &tpos, &pos);
	njPopMatrix(1);
	robo_smoke5.velo = velo;
	robo_smoke5.pos = pos;
	FUN_005536c0(&robo_smoke5);
}

// FUNCTION: SADX 0x005bed80
void RoboSearch(struct taskwk *twp, struct enemywk *ewp)
{
	if (RoboSearchPlayer(twp, ewp) != 0)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 3;
		twp->wtimer = 0;
		twp->flag &= ~0x100;
		ewp->sub_angle[5] = 0x1a0;
		ewp->sub_angle[2] = 0xb0;
	}
	ewp->acc.x = njCos(twp->ang.y) * ewp->weight * 0.02f;
	ewp->acc.z = njSin(-twp->ang.y) * ewp->weight * 0.02f;
	FUN_005bf0d0(twp, ewp);
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	ewp->sub_angle[6] += 0x300;
	ewp->sub_angle[0] += 0x1b0;
	ewp->nframe = njSin(ewp->sub_angle[6]) + 8.0;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
}

// STUB: SADX 0x005beef0
long RoboSearchPlayer(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// FUNCTION: SADX 0x005bf0d0
void FUN_005bf0d0(void *param_1, void *param_2)
{
	*(int *)((char *)param_2 + 0x1c0) = AdjustAngle(*(int *)((char *)param_2 + 0x1c0), *(int *)((char *)param_2 + 0x1d0), *(int *)((char *)param_2 + 0x1c4));
	*(int *)((char *)param_1 + 0x18) = AdjustAngle(*(int *)((char *)param_1 + 0x18), *(int *)((char *)param_2 + 0x1c0), *(int *)((char *)param_2 + 0x1b8));
}

// FUNCTION: SADX 0x005bf130
void RoboThrow(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (((local_8->flag & 0x200) != 0) && ((local_8->flag & 0x800) == 0))
	{
		ewp->old_mode = local_8->mode;
		local_8->mode = 4;
		local_8->wtimer = 0;
		if (tp->ctp != 0)
		{
			ewp->aim = tp->ctp->twp->pos;
		}
		ewp->sub_angle[5] = 0x500;
		ewp->sub_angle[2] = 0x3b0;
		*(int *)((char *)local_8->cwp->info + 0x34) |= 0x10;
	}
	FUN_005bf2c0(local_8, ewp);
	FUN_005be280((int)local_8, (int)ewp);
	FUN_005be2d0(local_8, ewp);
	EnemyCalcPlayerAngle(local_8, ewp, 0);
	FUN_005bf0d0(local_8, ewp);
	ewp->sub_angle[6] += 0x220;
	ewp->sub_angle[0] += 0x1b0;
	ewp->nframe = (float)(njSin(ewp->sub_angle[6]) + 8.0);
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	EnemyCheckGroundCollision(local_8, ewp);
	RoboDraw(local_8, ewp);
}

// FUNCTION: SADX 0x005bf2c0
void FUN_005bf2c0(struct taskwk *param_1, void *param_2)
{
	struct colliwk *local_8g;
	float local_cg;

	local_cg = EnemyDist2FromPlayer(param_1, 0);
	local_8g = param_1->cwp;
	if (local_cg < 3600.0f)
	{
		*(unsigned char *)((char *)param_2 + 0x49) = param_1->mode;
		param_1->mode = 8;
		param_1->wtimer = 0;
		param_1->flag = param_1->flag | 0x2800;
		param_1->smode = 0;
		*(float *)((char *)param_2 + 0x1ec) = 0.0f;
		*(float *)((char *)param_2 + 0x1e8) = 23.0f;
		*(float *)((char *)param_2 + 0x1e4) = *(float *)((char *)param_2 + 0x1e0);
	}
}

// FUNCTION: SADX 0x005bf360
void RoboScramble(struct taskwk *twp, struct enemywk *ewp)
{
	EnemyCalcAimAngle(twp, ewp);
	ewp->sub_angle[4] = AdjustAngle(ewp->sub_angle[4], ewp->aim_angle, 0x1a0);
	twp->ang.y = AdjustAngle(twp->ang.y, ewp->sub_angle[4], 0xb0);
	ewp->angz_spd = AdjustAngle(ewp->angz_spd, 0, 0x100);
	ewp->sub_angle[1] -= 0x100;
	if ((ewp->sub_angle[1] + 0x8000 & 0xffff) < 0x5800)
	{
		ewp->sub_angle[1] = 0xd800;
	}
	ewp->sub_angle[0] += 0x3800;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	if (ewp->nframe < 15.0f)
	{
		ewp->nframe += 0.09f;
	}
	if (ewp->force.z > 1.5f)
	{
		ewp->force.z -= 0.04f;
	}
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
	if (twp->wtimer > 0x3c)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 5;
		twp->wtimer = 0;
		ewp->sub_angle[5] = 0x300;
		ewp->sub_angle[2] = 0x1d0;
	}
}

// FUNCTION: SADX 0x005bf530
void RoboDash(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (tp->ctp != 0)
	{
		ewp->aim = tp->ctp->twp->pos;
	}
	EnemyCalcAimAngle(local_8, ewp);
	ewp->sub_angle[0] += 0x3800;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	ewp->acc.x = njCos(local_8->ang.y) * ewp->weight;
	ewp->acc.z = njSin(-local_8->ang.y) * ewp->weight;
	FUN_005bf0d0(local_8, ewp);
	FUN_005be280((int)local_8, (int)ewp);
	FUN_005be2d0(local_8, ewp);
	EnemyCheckGroundCollision(local_8, ewp);
	RoboDraw(local_8, ewp);
	RoboSmokeUnder(local_8, ewp);
	FUN_005bf870((int)local_8, (int)ewp);
	RoboSmokeGround(local_8, ewp);
	if ((ewp->aim.x - local_8->pos.x) * (ewp->aim.x - local_8->pos.x)
		+ (ewp->aim.z - local_8->pos.z) * (ewp->aim.z - local_8->pos.z) < 324.0f)
	{
		ewp->old_mode = local_8->mode;
		local_8->mode = 6;
		local_8->wtimer = 0;
		ewp->sub_angle[5] = 0x1a0;
		ewp->sub_angle[2] = 0xa0;
	}
}

// STUB: SADX 0x005bf6e0
void RoboSmokeGround(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005bf870
void FUN_005bf870(int param_1, int param_2)
{
	njPushMatrix(0);
	njUnitMatrix(0);
	njSetMatrix(0, (NJS_MATRIX *)(param_2 + 0x1fc));
	njCalcVector(0, &DAT_0264dbb8, &robo_jet.velo);
	njCalcPoint(0, &DAT_0264dbac, &robo_jet.pos);
	njPopMatrix(1);
	njAddVector(&robo_jet.velo, (struct NJS_POINT3 *)(param_2 + 4));
	CreateJet(&robo_jet);
}

// FUNCTION: SADX 0x005bf8f0
void RoboBrake(struct taskwk *twp, struct enemywk *ewp)
{
	ewp->sub_angle[1] += 0x400;
	if ((ewp->sub_angle[1] + 0x8000 & 0xffff) > 0xa000)
	{
		ewp->sub_angle[1] = 0x2000;
	}
	ewp->sub_angle[0] += 0x500;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	if (ewp->nframe > 8.0f)
	{
		ewp->nframe -= 0.1f;
	}
	if (ewp->force.z < 2.0f)
	{
		ewp->force.z += 0.02f;
	}
	FUN_005bf0d0(twp, ewp);
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
	if (twp->wtimer > 0xa)
	{
		RoboSmokeSide2(twp, ewp);
		ewp->acc.x -= ewp->velo.x * 0.025f;
		ewp->acc.z -= ewp->velo.z * 0.025f;
	}
	if (twp->wtimer > 0x28)
	{
		ewp->old_mode = twp->mode;
		twp->mode = 7;
		twp->wtimer = 0;
		ewp->sub_angle[6] = 0;
		ewp->aim_angle += 0x8000;
	}
}

// STUB: SADX 0x005bfab0
void RoboSmokeSide2(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005bfbf0
void RoboDocking(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	ewp->sub_angle[1] -= 0xb0;
	if (((ewp->sub_angle[1] + 0x8000) & 0xffff) < 0x8000)
	{
		ewp->sub_angle[1] = 0;
	}
	ewp->sub_angle[0] += 0x400;
	ewp->force.y = njSin(ewp->sub_angle[0]) * 0.5f;
	ewp->sub_angle[6] += 0x300;
	ewp->nframe = njSin(ewp->sub_angle[6]) + 8.0;
	FUN_005bf0d0(local_8, ewp);
	FUN_005be280((int)local_8, (int)ewp);
	FUN_005be2d0(local_8, ewp);
	EnemyCheckGroundCollision(local_8, ewp);
	RoboDraw(local_8, ewp);
	if ((local_8->flag & 0x100) != 0)
	{
		if (RoboSearchPlayer(local_8, ewp) != 0)
		{
			ewp->old_mode = local_8->mode;
			local_8->mode = 2;
			local_8->wtimer = 0;
			local_8->flag &= ~0x200;
		}
		else
		{
			if ((float)(rand() / 32768.0) > 0.5f)
			{
				ewp->old_mode = local_8->mode;
				local_8->mode = 0;
				local_8->wtimer = 0;
				local_8->flag |= 0x1000;
				local_8->flag &= ~0x200;
			}
			else
			{
				ewp->old_mode = local_8->mode;
				local_8->mode = 2;
				local_8->wtimer = 0;
				local_8->flag &= ~0x200;
			}
		}
	}
}

// FUNCTION: SADX 0x005bfdf0
void RoboCombo(struct taskwk *twp, struct enemywk *ewp)
{
	struct colliwk *local_8;
	local_8 = twp->cwp;
	FUN_005be2d0(twp, ewp);
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
	twp->mode = 0xa;
}
