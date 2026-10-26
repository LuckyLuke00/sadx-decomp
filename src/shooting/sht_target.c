#include "decls.h"
extern struct NJS_SPRITE lock_mk_spr;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;
extern int DAT_060ce45c;
extern int DAT_060ce460;
extern int DAT_060ce464;
extern int DAT_060ce468;
extern int DAT_060ce46c;
extern int DAT_060ce470;

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
	DAT_060ce45c = 0;
	DAT_060ce460 = 0;
	DAT_060ce464 = 0;
	DAT_060ce468 = 0;
	DAT_060ce46c = 0;
	DAT_060ce470 = 0;
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

// FUNCTION: SADX 0x007ebd90
void LockedEnemyDead(struct task *tp)
{
	struct task *var1 = (struct task *)tp->awp;
	tp->dest = (void (*)(struct task *))(*(int *)((char *)var1->twp + 8));
	tp->awp = 0;
	DestroyTask(var1);
	tp->dest(tp);
}

// STUB: SADX 0x007ebe20
void FUN_007ebe20(void)
{
}
