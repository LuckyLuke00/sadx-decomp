#include "decls.h"

// FUNCTION: SADX 0x0068c4c0
void ObjectSSElekanban(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->mode = 0;
	var1->smode = (SeqGetTime() == 2);
	tp->exec = (void (*)(struct task *))0x68c4a0;
	tp->disp = (void (*)(struct task *))0x68c3d0;
}
