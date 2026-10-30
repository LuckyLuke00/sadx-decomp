#include "decls.h"
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
void FUN_005bc3f0(void *param_1, void *param_2);
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

#pragma optimize("", off)
// STUB: SADX 0x005bc0f0
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
	if (twp->ang.y != 0)
	{
		njRotateY(0, (Uint16)twp->ang.y);
	}
	if (1)
	{
		njRotateY(0, 0x4000);
	}
	FUN_0067d2d0(0, 1.5f, 1.5f, 1.5f);
	njGetMatrix(&ewp->mat);
	njPopMatrix(1);
	njPushMatrix(0);
	njMultiMatrix(0, &ewp->mat);
	late_DrawModel((struct NJS_MODEL *)&model_sorsar_karada_1_atama1, 1);
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
	___dsSetPalette(0);
}
#pragma optimize("", on)

// STUB: SADX 0x005bc260
void RoboHeadExecutor(struct task *tp)
{
}

// STUB: SADX 0x005bc3f0
void FUN_005bc3f0(void *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x005bc470
void RoboHeadTakeOff(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	local_8g = *(float *)((char *)ewp + 0x130);
	if (local_cg->wtimer < 0x14)
	{
		RoboHeadSmokeSide(local_cg, ewp);
		*(float *)((char *)local_cg + 0x24) += 0.05f;
	}
	else
	{
		if (local_8g + 30.0f > *(float *)((char *)local_cg + 0x24))
		{
			*(float *)((char *)local_cg + 0x24) += 0.12f;
			RoboHeadSmokeUnder(local_cg, ewp);
		}
		else
		{
			ewp->old_mode = local_cg->mode;
			local_cg->mode = 2;
			local_cg->wtimer = 0;
			local_cg->cwp->flag &= ~0x1;
			*(float *)((char *)ewp + 0x78) = *(float *)((char *)local_cg + 0x24);
		}
	}
	EnemyCheckGroundCollision(local_cg, ewp);
	RoboHeadDraw(local_cg, ewp);
}

#pragma optimize("", off)
// STUB: SADX 0x005bc560
void RoboHeadSmokeSide(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x005bc6a0
void RoboHeadSmokeUnder(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005bc780
void RoboHeadChase(struct task *tp, struct enemywk *ewp)
{
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
	if (1)
	{
		njRotateX(0, 0xc000);
	}
	FUN_0067d2d0(0, local_8g, local_8g, local_8g);
	late_DrawSprite3D(&sprite_robo_beam, 0, 0x22, 4);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005bd0b0
void RoboHeadUp(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;
	local_8 = *(float *)((char *)ewp + 0x130);
	if (EnemyDist2FromPlayer(twp, 0) < 900.0f && (DAT_05baf368[0]->flag & 0x8000) == 0)
	{
		twp->pos.y += 1.2f;
		if (twp->pos.y > *(float *)((char *)ewp + 0x78) + 20.0f)
		{
			twp->pos.y = *(float *)((char *)ewp + 0x78) + 20.0f;
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

// STUB: SADX 0x005bd170
void RoboHeadWait(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_cg = tp->twp;
	struct enemywk *local_8g = (struct enemywk *)DAT_05baf368[0];
	*(int *)((char *)local_cg + 0x18) -= 0x400;
	*(float *)((char *)ewp + 0x10) -= *(float *)((char *)ewp + 4) * 0.05f;
	*(float *)((char *)ewp + 0x18) -= *(float *)((char *)ewp + 0xc) * 0.05f;
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

// STUB: SADX 0x005bd270
void RoboHeadReturn(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bd410
void RoboHeadDocking(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bd920
void RoboDestructor(struct task *tp)
{
}

// STUB: SADX 0x005bd990
void RoboExecutor(struct task *tp)
{
}

// STUB: SADX 0x005bdc30
void FUN_005bdc30(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x005bdcb0
void RoboEditMode(struct taskwk *twp)
{
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

// STUB: SADX 0x005bdf30
void RoboSwing(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005be1b0
void RoboBumpSide(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005be720
void RoboSleep(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005be930
long RoboHearSound(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// FUNCTION: SADX 0x005be9b0
void RoboWakeUp(struct taskwk *twp, struct enemywk *ewp)
{
	unsigned short local_8;
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	*(int *)((char *)ewp + 0x1b4) = AdjustAngle(*(int *)((char *)ewp + 0x1b4), 0, 0xb0);
	if (*(float *)((char *)ewp + 0x7c) < 2.1f)
	{
		*(float *)((char *)ewp + 0x7c) += 0.05f;
	}
	*(int *)((char *)ewp + 0x1b0) += 0x190;
	*(float *)((char *)ewp + 0x78) = njSin(*(int *)((char *)ewp + 0x1b0)) * 0.5f;
	if (*(float *)((char *)ewp + 0x1e0) < 9.0f)
	{
		*(float *)((char *)ewp + 0x1e0) += 0.22f;
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
		*(int *)((char *)ewp + 0x1c8) = 0x4000;
		ewp->old_mode = twp->mode;
		twp->mode = 2;
		twp->wtimer = 0;
		*(int *)((char *)ewp + 0x1c4) = 0x1a0;
		*(int *)((char *)ewp + 0x1b8) = 0x70;
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
		*(long *)((char *)ewp + 0x1c4) = 0x1a0;
		*(long *)((char *)ewp + 0x1b8) = 0xb0;
	}
	ewp->acc.x = njCos(*(long *)((char *)twp + 0x18)) * ewp->weight * 0.02f;
	*(float *)((char *)ewp + 0x18) = njSin(-*(long *)((char *)twp + 0x18)) * ewp->weight * 0.02f;
	FUN_005bf0d0(twp, ewp);
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	*(long *)((char *)ewp + 0x1c8) += 0x300;
	*(long *)((char *)ewp + 0x1b0) += 0x1b0;
	ewp->nframe = njSin(*(long *)((char *)ewp + 0x1c8)) + 8.0;
	*(float *)((char *)ewp + 0x78) = njSin(*(long *)((char *)ewp + 0x1b0)) * 0.5f;
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
			*(NJS_POINT3 *)((char *)ewp + 0x5c) = *(NJS_POINT3 *)((char *)tp->ctp->twp + 0x20);
		}
		*(int *)((char *)ewp + 0x1c4) = 0x500;
		*(int *)((char *)ewp + 0x1b8) = 0x3b0;
		*(int *)((char *)local_8->cwp->info + 0x34) |= 0x10;
	}
	FUN_005bf2c0(local_8, ewp);
	FUN_005be280((int)local_8, (int)ewp);
	FUN_005be2d0(local_8, ewp);
	EnemyCalcPlayerAngle(local_8, ewp, 0);
	FUN_005bf0d0(local_8, ewp);
	*(int *)((char *)ewp + 0x1c8) += 0x220;
	*(int *)((char *)ewp + 0x1b0) += 0x1b0;
	ewp->nframe = (float)(njSin(*(int *)((char *)ewp + 0x1c8)) + 8.0);
	*(float *)((char *)ewp + 0x78) = njSin(*(int *)((char *)ewp + 0x1b0)) * 0.5f;
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

// STUB: SADX 0x005bf360
void RoboScramble(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bf530
void RoboDash(struct task *tp, struct enemywk *ewp)
{
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
	*(int *)((char *)ewp + 0x1b4) += 0x400;
	if ((*(int *)((char *)ewp + 0x1b4) + 0x8000 & 0xffff) > 0xa000)
	{
		*(int *)((char *)ewp + 0x1b4) = 0x2000;
	}
	*(int *)((char *)ewp + 0x1b0) += 0x500;
	*(float *)((char *)ewp + 0x78) = njSin(*(int *)((char *)ewp + 0x1b0)) * 0.5f;
	if (*(float *)((char *)ewp + 0x1e0) > 8.0f)
	{
		*(float *)((char *)ewp + 0x1e0) -= 0.1f;
	}
	if (*(float *)((char *)ewp + 0x7c) < 2.0f)
	{
		*(float *)((char *)ewp + 0x7c) += 0.02f;
	}
	FUN_005bf0d0(twp, ewp);
	FUN_005be280((int)twp, (int)ewp);
	FUN_005be2d0(twp, ewp);
	EnemyCheckGroundCollision(twp, ewp);
	RoboDraw(twp, ewp);
	if (twp->wtimer > 0xa)
	{
		RoboSmokeSide2(twp, ewp);
		*(float *)((char *)ewp + 0x10) -= *(float *)((char *)ewp + 4) * 0.025f;
		*(float *)((char *)ewp + 0x18) -= *(float *)((char *)ewp + 0xc) * 0.025f;
	}
	if (twp->wtimer > 0x28)
	{
		*(char *)((char *)ewp + 0x49) = twp->mode;
		twp->mode = 7;
		twp->wtimer = 0;
		*(int *)((char *)ewp + 0x1c8) = 0;
		*(int *)((char *)ewp + 0x1d0) += 0x8000;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x005bfab0
void RoboSmokeSide2(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005bfbf0
void RoboDocking(struct task *tp, struct enemywk *ewp)
{
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
