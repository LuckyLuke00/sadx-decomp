#include "decls.h"

// FUNCTION: SADX 0x00895a40
void hallgate_draw(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsAction(action_hallgate, var1->counter.f, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00895c40
void hallgate_o_switch_exec(struct task *task_p)
{
}

// FUNCTION: SADX 0x00895cd0
void hallgate_o_switch_end(struct task *task_p)
{
	struct task *var1;
	struct taskwk *var2;
	var1 = task_p->ptp;
	var2 = var1->twp;
	(*(void (*)(struct task *))var2->value.ptr)(task_p);
	var2->value.l = 0;
	var2->timer.l = 0;
}
