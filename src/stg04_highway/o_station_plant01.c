#include "decls.h"
static void Exec(struct task *tp);
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	SetObjectTexture();
	___dsDrawObject((struct obj *)&object_stobj_fplant01_fplant01);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0081e5b0
static void Exec(struct task *tp)
{
	struct taskwk *var1;

	if (CheckRangeOut(tp))
	{
		return;
	}
	var1 = tp->twp;
	Draw(tp);
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0081e5f0
void ObjectStationPlant01(struct task *tp)
{
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->exec = Exec;
	tp->disp = Draw;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, colli, 1, 4);
		SET_COLLI_RANGE(tp->twp->cwp, 32.0f);
	}
}
