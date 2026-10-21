#include "decls.h"

// FUNCTION: SADX 0x0049a9f0
void ObjectMi3Dasu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		var1->wtimer = 0;
		tp->exec = (void (*)(struct task *))0x49a8a0;
		tp->dest = (void (*)(struct task *))0x49a840;
		tp->disp = (void (*)(struct task *))0x49a770;
	}
}
