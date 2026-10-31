#include "decls.h"
static void Exec(struct task *tp);
extern struct obj object_mi_flag[];
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0049a5b0
static void Disp(struct task *tp)
{
	struct taskwk *var2 = tp->twp;
	___njSetTexture(&texlist_kariobj);
	njPushMatrix(0);
	njTranslateV(0, &var2->pos);
	njScaleV(0, &var2->scl);
	late_DrawObjectMesh(&object_mi_flag[0], 0);
	njPopMatrix(1);
}

// STUB: SADX 0x0049a600
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049a740
void ObjectMiTest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 0.0f;
	var1->wtimer = 0x14;
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
