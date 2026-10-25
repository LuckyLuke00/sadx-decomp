#include "decls.h"

// STUB: SADX 0x0087fd20
void ObjectKazariYajiNeon(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->scl.y == 0.0f)
	{
		var1->mode = 1;
	}
	else if (var1->scl.y == 1.0f)
	{
		var1->mode = 2;
	}
	else
	{
		var1->mode = 3;
	}
	tp->twp->counter.f = 0.0f;
	tp->twp->btimer = 0;
	tp->exec = (void (*)(struct task *))0x87fc80;
	tp->disp = (void (*)(struct task *))0x87fb50;
	tp->dest = (void (*)(struct task *))0x7d21b0;
}

// STUB: SADX 0x0087fd80
void ObjectKazariDensyoku(struct task *tp)
{
}
