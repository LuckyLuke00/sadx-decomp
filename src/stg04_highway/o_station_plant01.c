#include "decls.h"
extern struct obj object_stobj_fplant01_fplant01[];
static void Draw(struct task *tp);

// FUNCTION: SADX 0x0081e550
static void Draw(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	SetObjectTexture();
	___dsDrawObject((struct obj *)&object_stobj_fplant01_fplant01);
	njPopMatrix(1);
}

// STUB: SADX 0x0081e5f0
void ObjectStationPlant01(struct task *tp)
{
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->exec = (void (__cdecl *)(struct task *))0x81e5b0;
	tp->disp = Draw;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)&colli, 1, 4);
		SET_COLLI_RANGE(tp->twp->cwp, 32.0);
	}
}
