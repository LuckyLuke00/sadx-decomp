#include "decls.h"
void FUN_005be280(int param_1, int param_2);
void FUN_005be2d0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005bf2c0(struct taskwk *param_1, void *param_2);
void FUN_005bf0d0(void *param_1, void *param_2);
extern struct NJS_SPRITE sprite_robo_beam;
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x005bc0c0
void RoboHeadDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	RoboHeadDraw(local_cg, local_8g);
}

// STUB: SADX 0x005bc3f0
void FUN_005bc3f0(void *param_1, void *param_2)
{
}

// STUB: SADX 0x005bc470
void RoboHeadTakeOff(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bc6a0
void RoboHeadSmokeUnder(struct taskwk *twp, struct enemywk *ewp)
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

// FUNCTION: SADX 0x005bcd10
void RoboBeamDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	local_8g = local_cg->scl.x;
	if (dsCheckViewV(&local_cg->pos, 10.0f) == 0)
	{
		return;
	}
	SetMaterial(local_cg->scl.z, 1.0f, 1.0f, 1.0f);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 10);
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	if (1)
	{
		njRotateX(0, 0xc000);
	}
	FUN_0067d2d0(0, local_8g, local_8g, local_8g);
	late_DrawSprite3D(&sprite_robo_beam, 1, 0x22, 4);
	njPopMatrix(1);
}

// STUB: SADX 0x005bcfb0
void RoboBeam2Displayer(struct task *tp)
{
}

// STUB: SADX 0x005bd0b0
void RoboHeadUp(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bd170
void RoboHeadWait(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bd270
void RoboHeadReturn(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bd920
void RoboDestructor(struct task *tp)
{
}

// STUB: SADX 0x005bdc30
void FUN_005bdc30(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bdcb0
void RoboEditMode(struct taskwk *twp)
{
}

// STUB: SADX 0x005bde30
void FUN_005bde30(struct task *pTask, struct OBJ_CONDITION *ocp, void *param_3)
{
}

// FUNCTION: SADX 0x005bdea0
void FUN_005bdea0(struct taskwk *param_1)
{
	CreateFlash2(param_1->pos.x, param_1->pos.y + 5.0f, param_1->pos.z, 1.4f);
	CreateExpSpring(param_1, 8);
	CreateAnimal(8, param_1->pos.x, param_1->pos.y + 15.0f, param_1->pos.z);
}

// STUB: SADX 0x005be1b0
void RoboBumpSide(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005be930
long RoboHearSound(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// STUB: SADX 0x005be9b0
void RoboWakeUp(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005beb60
void RoboSmokeSide(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005beca0
void RoboSmokeUnder(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bed80
void RoboSearch(struct taskwk *twp, struct enemywk *ewp)
{
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

// STUB: SADX 0x005bf130
void RoboThrow(struct task *tp, struct enemywk *ewp)
{
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

// STUB: SADX 0x005bfab0
void RoboSmokeSide2(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bfbf0
void RoboDocking(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005bfdf0
void RoboCombo(struct taskwk *twp, struct enemywk *ewp)
{
}
