#include "decls.h"
extern struct obj object_mi_kinka[];
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0049c460
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_kariobj);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.x + 16384 != 0)
	{
		njRotateX(0, (unsigned short)(16384 + var1->ang.x));
	}
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	___dsDrawObject(&object_mi_kinka[0]);
	njPopMatrix(1);
	Shadow(var1, 1.0f);
}

// STUB: SADX 0x0049c4f0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049c780
void ObjectMiKinka(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		*(int *)((char *)var1 + 0x14) = 0;
		*(int *)((char *)var1 + 0x1c) = 0;
		CCL_Init(tp, mi_kinka_colli_info, 1, 4);
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
