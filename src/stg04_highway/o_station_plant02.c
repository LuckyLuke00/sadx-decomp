#include "decls.h"
static void Draw(struct task *tp);
extern struct obj object_stobj_fplant02_fplant02[1];

// FUNCTION: SADX 0x0081e4b0
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	SetObjectTexture();
	___dsDrawObject((struct obj *)&object_stobj_fplant02_fplant02);
	njPopMatrix(1);
}

// STUB: SADX 0x0081e530
void ObjectStationPlant02(struct task *tp)
{
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->exec = (void (__cdecl *)(struct task *))0x81e510;
	tp->disp = Draw;
}
