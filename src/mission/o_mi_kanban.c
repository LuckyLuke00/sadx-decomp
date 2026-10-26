#include "decls.h"
void FUN_00422560(int param_1);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0049c290
static void Disp(struct task *tp)
{
	struct taskwk *var2 = tp->twp;
	unsigned char *var3 = *(unsigned char **)((char *)tp->ocp + 0x10);
	___njSetTexture(&texlist_kariobj);
	FUN_00422560(3);
	njPushMatrix(0);
	matlist_mi_kanban_ita3[0].attr_texId = (unsigned long)((int)var3[8] % 5) + 7;
	njTranslateV(0, &var2->pos);
	if (var2->ang.y != 0)
	{
		njRotateY(0, (unsigned short)var2->ang.y);
	}
	njScaleV(0, &var2->scl);
	___dsDrawObject((struct obj *)&object_mi_kanban_ita);
	njPopMatrix(1);
	npSetZCompare();
}

// STUB: SADX 0x0049c320
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049c420
void ObjectMiKanban(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		var1->ang.x = 0;
		var1->ang.z = 0;
		var1->mode = 0;
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
