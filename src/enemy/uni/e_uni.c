#include "decls.h"
extern struct obj object_uni_a_unibody_unibody[];
extern struct NJS_TEXLIST texlist_uni_a_unibody;
void CheckParentDeath(struct task *tp, struct enemywk *ewp);
void FUN_005ca750(struct task *param_1, struct taskwk *param_2);
void UniTogeADraw(struct taskwk *twp, struct enemywk *ewp);
void EnemyCheckGroundCollision(struct taskwk *twp, struct enemywk *ewp);
extern double DAT_00962f10;
void FUN_005ccf30(struct task *param_1, struct motionwk *param_2);
void FUN_005cd2c0(struct task *param_1, struct enemywk *param_2);
void FUN_005cc030(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005cc0a0(struct task *param_1, struct enemywk *param_2);
void FUN_005cad80(struct task *param_1, struct taskwk *param_2, struct motionwk *param_3);
void FUN_005cae50(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005cafa0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_005cad80(struct task *param_1, struct taskwk *param_2, struct motionwk *param_3);
void FUN_005caab0(struct task *param_1, struct task *param_2);
static void UniCDraw(struct taskwk *twp, struct enemywk *ewp);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
extern struct NJS_TEXLIST texlist_uni_c_unibody;
extern struct obj object_uni_c_fireball_fireball[1];
extern struct NJS_TEXLIST texlist_togeball_togeball;
extern struct obj object_togeball_togeball_togeball;
struct task;
struct enemywk;
void FUN_005ca750(struct task *param_1, struct taskwk *param_2);
void FUN_005ca420(struct task *param_1);
void UniADraw(struct taskwk *twp, struct enemywk *ewp);
signed char EnemySearchPlayer(struct taskwk *twp, struct enemywk *ewp);
long EnemyTurnToHome(struct taskwk *twp, struct enemywk *ewp);
long EnemyTurnToPlayer(struct taskwk *twp, struct enemywk *ewp, unsigned char pnum);

// STUB: SADX 0x005ca330
void UniTogeAExecutor(struct task *tp)
{
}

// STUB: SADX 0x005ca420
void FUN_005ca420(struct task *tp)
{
}

// STUB: SADX 0x005ca670
void UniTogeAThrown(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005ca750
void FUN_005ca750(struct task *tp, struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005ca7c0
void UniADisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	UniADraw(local_cg, local_8g);
}

// STUB: SADX 0x005ca7f0
void UniADraw(struct taskwk *twp, struct enemywk *ewp)
{
	float local_cg;
	float local_8g;
	local_cg = twp->scl.x;
	local_8g = twp->scl.y;
	if (dsCheckViewV(&twp->pos, 20.0f) == 0)
	{
		return;
	}
	___njSetTexture(&texlist_uni_a_unibody);
	ResetMaterial();
	njPushMatrix(0);
	FUN_0067d830(0, twp->pos.x, njSin(ewp->sub_angle[0]) * 0.4000000059604645f + twp->pos.y, twp->pos.z);
	if (*(int *)((char *)twp + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)twp + 0x18));
	}
	if (1)
	{
		njRotateY(0, 0x8000);
	}
	___dsDrawObject((struct obj *)&object_uni_a_unibody_unibody);
	njPopMatrix(1);
	dispPoliceShadow(twp, ewp);
}

// STUB: SADX 0x005ca8f0
void UniAExecutor(struct task *tp)
{
}

// STUB: SADX 0x005caab0
void FUN_005caab0(struct task *tp, struct task *param_2)
{
}

// FUNCTION: SADX 0x005cad80
void FUN_005cad80(struct task *param_1, struct taskwk *param_2, struct motionwk *param_3)
{
	FUN_005b5aa0(param_1, param_2, param_3);
	DeadOut(param_1);
	param_1->exec = FreeTaskC;
	FUN_005e5770(param_1);
}

// FUNCTION: SADX 0x005cadc0
void UniDead(struct taskwk *twp, struct enemywk *ewp)
{
	CreateFlash2(twp->pos.x, twp->pos.y + 5.0f, twp->pos.z, 1.4f);
	CreateExpSpring(twp, 8);
	CreateAnimal(0, twp->pos.x, twp->pos.y + 15.0f, twp->pos.z);
}

// FUNCTION: SADX 0x005cae50
void FUN_005cae50(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005caec0(param_1, param_2);
	UniADraw(param_1, param_2);
	if (EnemySearchPlayer(param_1, param_2) != 0)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 2;
		param_1->wtimer = 0;
	}
}

// FUNCTION: SADX 0x005caec0
void FUN_005caec0(struct taskwk *param_1, struct enemywk *param_2)
{
	param_2->acc.x = -param_2->velo.x * 0.029999999329447746f + param_2->acc.x;
	param_2->acc.y = -param_2->velo.y * 0.029999999329447746f + param_2->acc.y;
	param_2->acc.z = -param_2->velo.z * 0.029999999329447746f + param_2->acc.z;
	param_2->velo.x += param_2->acc.x;
	param_2->velo.y += param_2->acc.y;
	param_2->velo.z += param_2->acc.z;
	param_1->pos.x += param_2->velo.x;
	param_1->pos.y += param_2->velo.y;
	param_1->pos.z += param_2->velo.z;
	param_2->acc.x = 0.0f;
	param_2->acc.y = 0.0f;
	param_2->acc.z = 0.0f;
}

// FUNCTION: SADX 0x005cafa0
void FUN_005cafa0(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005cb140(param_1, param_2);
	FUN_005cb0d0(param_1, param_2);
	if (FUN_005cb070(param_1, param_2) != 0)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 3;
		param_1->wtimer = 0;
	}
	param_2->acc.x = njCos(param_1->ang.y) * 0.019999999552965164f;
	param_2->acc.z = njSin(-param_1->ang.y) * 0.019999999552965164f;
	FUN_005caec0(param_1, param_2);
	FUN_005cb190((struct task *)param_1, param_2);
	UniADraw(param_1, param_2);
}

// FUNCTION: SADX 0x005cb070
long FUN_005cb070(struct taskwk *param_1, struct enemywk *param_2)
{
	if ((param_1->flag & 0x200) != 0)
	{
		EnemyTurnToHome(param_1, param_2);
	}
	else
	{
		if ((param_1->flag & 0x400) != 0)
		{
			if (EnemyTurnToPlayer(param_1, param_2, 0) < 0x100)
			{
				return 1;
			}
		}
	}
	return 0;
}

// STUB: SADX 0x005cb0d0
void FUN_005cb0d0(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005cb140
void FUN_005cb140(struct taskwk *param_1, struct enemywk *param_2)
{
	if (EnemySearchPlayer(param_1, param_2) != 0)
		param_1->flag |= 0x400;
	else
		param_1->flag &= 0xfffffbff;
}

// STUB: SADX 0x005cb190
void FUN_005cb190(struct task *tp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005cb270
void FUN_005cb270(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005cb140(param_1, param_2);
	FUN_005cb0d0(param_1, param_2);
	FUN_005cb070(param_1, param_2);
	FUN_005caab0((struct task *)param_1, (struct task *)param_2);
	param_2->acc.x = njCos(param_1->ang.y) * 0.019999999552965164f;
	param_2->acc.z = njSin(-param_1->ang.y) * 0.019999999552965164f;
	FUN_005caec0(param_1, param_2);
	FUN_005cb190((struct task *)param_1, param_2);
	UniADraw(param_1, param_2);
}

// FUNCTION: SADX 0x005cb7b0
void UniTogeADisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	___njSetTexture(&texlist_togeball_togeball);
	ResetMaterial();
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	if (*(int *)((char *)local_cg + 0x1c) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)local_cg + 0x1c));
	}
	if (local_cg->ang.x != 0)
	{
		njRotateX(0, local_cg->ang.x);
	}
	___dsDrawObject(&object_togeball_togeball_togeball);
	njPopMatrix(1);
	dispPoliceShadow(local_cg, local_8g);
}

// STUB: SADX 0x005cb860
void UniTogeBExecutor(struct task *tp)
{
}

// STUB: SADX 0x005cb980
void FUN_005cb980(struct task *tp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005cbb80
void UniTogeADraw(struct taskwk *twp, struct enemywk *ewp)
{
	if (dsCheckViewV(&twp->pos, 20.0f) == 0)
	{
		return;
	}
	___njSetTexture(&texlist_togeball_togeball);
	twp->ang.x += 0x200;
	twp->ang.z += 0x300;
	ResetMaterial();
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)twp->ang.z);
	}
	if (twp->ang.x != 0)
	{
		njRotateX(0, (unsigned short)twp->ang.x);
	}
	___dsDrawObject(&object_togeball_togeball_togeball);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005cbe60
void FUN_005cbe60(struct task *param_1, struct taskwk *param_2)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;
	local_cg = param_1->twp;
	local_8g = param_1->ptp->twp;
	if (*(char *)local_8g == 9)
	{
		((char *)param_2)[0x49] = *(char *)local_cg;
		*(char *)local_cg = 3;
		*(short *)((char *)local_cg + 6) = 0;
	}
}

// STUB: SADX 0x005cbeb0
void UniBExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x005cc030
void FUN_005cc030(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005caec0(param_1, param_2);
	UniADraw(param_1, param_2);
	if (EnemySearchPlayer(param_1, param_2) != 0)
	{
		param_2->old_mode = param_1->mode;
		param_1->mode = 6;
		param_1->wtimer = 0;
	}
}

// FUNCTION: SADX 0x005cc0a0
void FUN_005cc0a0(struct task *param_1, struct enemywk *param_2)
{
	struct taskwk *local_8;

	local_8 = *(struct taskwk **)((char *)param_1 + 0x38);
	FUN_005cb140((struct taskwk *)param_1, param_2);
	FUN_005cb0d0((struct taskwk *)param_1, param_2);
	FUN_005cb070((struct taskwk *)param_1, param_2);
	param_2->acc.x = njCos((int)param_1->dest) * 0.019999999552965164;
	param_2->acc.z = njSin(-(int)param_1->dest) * 0.019999999552965164;
	FUN_005caec0((struct taskwk *)param_1, param_2);
	FUN_005cb190(param_1, param_2);
	UniADraw((struct taskwk *)param_1, param_2);
}

// FUNCTION: SADX 0x005cc5f0
void UniTogeCDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	___njSetTexture(&texlist_uni_c_unibody);
	ResetMaterial();
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	if (*(int *)((char *)local_cg + 0x1c) != 0)
	{
		njRotateZ(0, (int)*(unsigned short *)((char *)local_cg + 0x1c));
	}
	if (*(int *)((char *)local_cg + 0x14) != 0)
	{
		njRotateX(0, *(unsigned short *)((char *)local_cg + 0x14));
	}
	FUN_0067d2d0(0, 0.6f, 0.6f, 0.6f);
	___dsDrawModel((struct NJS_MODEL *)*(int *)((char *)&object_uni_c_fireball_fireball + 4));
	njPopMatrix(1);
	dispPoliceShadow(local_cg, local_8g);
}

// STUB: SADX 0x005cc6c0
void FUN_005cc6c0(struct task *param_1)
{
}

// STUB: SADX 0x005ccc50
void CheckParentDeath(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005ccf30
void FUN_005ccf30(struct task *tp, struct motionwk *mwp)
{
}

// FUNCTION: SADX 0x005cd2c0
void FUN_005cd2c0(struct task *param_1, struct enemywk *param_2)
{
	struct taskwk *local_cg;
	struct colliwk *local_8g;
	local_cg = param_1->twp;
	local_8g = local_cg->cwp;
	FUN_005cd340((float *)local_cg, (float *)param_2);
	EnemyCheckGroundCollision(local_cg, param_2);
	UniTogeCDraw(local_cg, param_2);
	if ((param_2->flag & 0x10) != 0)
	{
		param_2->old_mode = local_cg->mode;
		local_cg->mode = 5;
		local_cg->wtimer = 0;
	}
}

// FUNCTION: SADX 0x005cd340
void FUN_005cd340(float *param_1, float *param_2)
{
	param_2[4] = -param_2[1] * 0.029999999329447746 * 0.4000000059604645 + param_2[4];
	param_2[6] = -param_2[3] * 0.029999999329447746 * 0.4000000059604645 + param_2[6];
	param_2[1] += param_2[4];
	param_2[2] = param_2[5] - 0.30000001192092896 + param_2[2];
	param_2[3] += param_2[6];
	param_1[8] += param_2[1];
	param_1[9] += param_2[2];
	param_1[10] += param_2[3];
	param_2[4] = 0.0f;
	param_2[5] = 0.0f;
	param_2[6] = 0.0f;
}

// FUNCTION: SADX 0x005cd410
void UniCDisplayer(struct task *tp)
{
	struct taskwk *local_cg;
	struct enemywk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct enemywk *)tp->mwp;
	UniCDraw(local_cg, local_8g);
}

// STUB: SADX 0x005cd440
static void UniCDraw(struct taskwk *twp, struct enemywk *ewp)
{
	float local_cg;
	float local_8g;
	local_cg = twp->scl.x;
	local_8g = twp->scl.y;
	if (dsCheckViewV(&twp->pos, 20.0f) == 0)
	{
		return;
	}
	___njSetTexture(&texlist_uni_c_unibody);
	ResetMaterial();
	njPushMatrix(0);
	FUN_0067d830(0, twp->pos.x, njSin(ewp->sub_angle[0]) * 0.4000000059604645f + twp->pos.y, twp->pos.z);
	if (*(int *)((char *)twp + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)twp + 0x18));
	}
	if (1)
	{
		njRotateY(0, 0x8000);
	}
	___dsDrawObject((struct obj *)&object_uni_c_unibody_unibody);
	njPopMatrix(1);
	dispPoliceShadow(twp, ewp);
}

// STUB: SADX 0x005cd540
void UniCExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x005cd910
void UniCNormal(struct taskwk *twp, struct enemywk *ewp)
{
	struct colliwk *local_8;
	local_8 = twp->cwp;
	FUN_005cb140(twp, ewp);
	FUN_005cb0d0(twp, ewp);
	FUN_005cb070(twp, ewp);
	ewp->acc.x = njCos(twp->ang.y) * DAT_00962f10;
	ewp->acc.z = njSin(-twp->ang.y) * DAT_00962f10;
	FUN_005caec0(twp, ewp);
	FUN_005cb190((struct task *)twp, ewp);
	UniCDraw(twp, ewp);
	dsPlay_timer_v(0x35a, (int)twp, 1, 0, 1, twp->pos.x, twp->pos.y, twp->pos.z);
	ewp->sub_angle[0] += 0x300;
}
