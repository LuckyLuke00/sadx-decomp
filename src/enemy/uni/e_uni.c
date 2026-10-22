#include "decls.h"
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
void FUN_005e5770(struct task *param_1);
void FreeTaskC(struct task *tp);
void DeadOut(struct task *pTask);

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
}

// STUB: SADX 0x005caab0
void FUN_005caab0(struct task *tp, struct task *param_2)
{
}

// FUNCTION: SADX 0x005cad80
void FUN_005cad80(struct task *param_1, struct taskwk *param_2, struct motionwk *param_3)
{
	((void (*)(struct task *, struct taskwk *, struct motionwk *))FUN_005b5aa0)(param_1, param_2, param_3);
	DeadOut(param_1);
	param_1->exec = FreeTaskC;
	FUN_005e5770(param_1);
}

// STUB: SADX 0x005cadc0
void UniDead(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cae50
void FUN_005cae50(struct taskwk *twp, struct enemywk *ewp)
{
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

// STUB: SADX 0x005cafa0
void FUN_005cafa0(struct taskwk *twp, struct enemywk *ewp)
{
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

// STUB: SADX 0x005cbe60
void FUN_005cbe60(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x005cc030
void FUN_005cc030(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cc0a0
void FUN_005cc0a0(struct task *tp, struct enemywk *ewp)
{
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

// STUB: SADX 0x005ccc50
void CheckParentDeath(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cd2c0
void FUN_005cd2c0(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cd340
void FUN_005cd340(float *param_1, float *param_2)
{
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
void UniCDraw(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005cd540
void UniCExecutor(struct task *tp)
{
}

// STUB: SADX 0x005cd910
void UniCNormal(struct taskwk *twp, struct enemywk *ewp)
{
}
