#include "decls.h"

// FUNCTION: SADX 0x0068c5f0
void ObjectSSShop2robot(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = (void (*)(struct task *))0x68c580;
	tp->disp = (void (*)(struct task *))0x68c580;
}
