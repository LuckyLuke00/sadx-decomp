#include "decls.h"
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

// STUB: SADX 0x007ebba0
void InvertPos(struct task *tp)
{
}
