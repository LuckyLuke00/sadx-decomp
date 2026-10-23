#include "decls.h"

// STUB: SADX 0x00808490
void ObjectWindyHasiEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x00808560
void ObjectWindyHaneA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = (void *)0x3b3805c;
	CCL_Init(tp, (struct CCL_INFO *)0x3b755c8, 2, 4);
	var1->timer.b[0] = 2;
	tp->exec = (void (*)(struct task *))0x808400;
	tp->disp = (void (*)(struct task *))0x807f30;
}
