#include "decls.h"
extern struct NJS_SPRITE lock_mk_spr;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;
extern int DAT_060ce45c[6];

// FUNCTION: SADX 0x007eb680
void TargetDisp2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 10);
		___njColorBlendingMode(1, 10);
		SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
		___njSetTexture(&lock_mk_list);
		lock_mk_spr.p.x = var1->pos.x;
		lock_mk_spr.p.y = var1->pos.y;
		lock_mk_spr.sx = 1.0f;
		lock_mk_spr.sy = 1.0f;
	}
}

// FUNCTION: SADX 0x007eb7c0
void LockOnListInit()
{
	DAT_060ce45c[0] = 0;
	DAT_060ce45c[1] = 0;
	DAT_060ce45c[2] = 0;
	DAT_060ce45c[3] = 0;
	DAT_060ce45c[4] = 0;
	DAT_060ce45c[5] = 0;
}

// FUNCTION: SADX 0x007ebba0
void InvertPos(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;

	var1->pos.x = var2->pos.x - DAT_0629c6ec;
	var1->pos.y = var2->pos.y - DAT_0629c6f0;
	var1->pos.z = 1000.0f;
	njPushMatrix(0);
	njInvertMatrix(0);
	njCalcPoint(0, &var1->pos, &var1->pos);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007ebc00
void LockOnDisp(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_POINT2 pd;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		if (StageEventCheck() == 0)
		{
			if (ChkPause() == 0)
			{
				njPushMatrix(NULL);
				___njColorBlendingMode(0, 10);
				___njColorBlendingMode(1, 10);
				SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
				___njSetTexture(&lock_mk_list);
				njProjectScreen(NULL, &var1->pos, &pd);
				lock_mk_spr.p.x = pd.x;
				lock_mk_spr.p.y = pd.y;
				lock_mk_spr.sx = *(float *)((char *)var1 + 0x30) * ScreenRaitoY;
				lock_mk_spr.sy = *(float *)((char *)var1 + 0x30) * ScreenRaitoY;
				FUN_00472980(&lock_mk_spr, 2, 1000.0f, 0x22);
				njPopMatrix(1);
				___njColorBlendingMode(0, 8);
				___njColorBlendingMode(1, 6);
				ResetMaterial();
			}
		}
	}
}

// FUNCTION: SADX 0x007ebd90
void LockedEnemyDead(struct task *tp)
{
	struct task *var1 = (struct task *)tp->awp;
	tp->dest = (void (*)(struct task *))(*(int *)((char *)var1->twp + 8));
	tp->awp = 0;
	DestroyTask(var1);
	tp->dest(tp);
}

// FUNCTION: SADX 0x007ebdf0
int FUN_007ebdf0(int param_1)
{
	int var1;

	for (var1 = 0; var1 < 6; var1++)
	{
		if (DAT_060ce45c[var1] == param_1)
		{
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x007ebe20
void FUN_007ebe20(void)
{
}

// FUNCTION: SADX 0x007ebe80
void LockOnDead(struct task *tp)
{
	int var3;
	struct task *var1;
	struct taskwk *var2;
	var3 = 0;
	while (var3 < 6)
	{
		if ((DAT_060ce45c[var3] == 0) || (DAT_060ce45c[var3] != (int)tp->ptp))
		{
			var3 = var3 + 1;
		}
		else
		{
			DAT_060ce45c[var3] = 0;
			break;
		}
	}
	var1 = tp->ptp;
	if (var1->awp != 0)
	{
		var2 = tp->twp;
		var1->dest = (void (*)(struct task *))var2->counter.ptr;
		var1->awp = 0;
	}
	tp->ptp = 0;
}
