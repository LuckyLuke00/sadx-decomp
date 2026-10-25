#include "decls.h"

// STUB: SADX 0x008829b0
void ObjectHoudaiR(struct task *tp)
{
	tp->twp->mode = 1;
	tp->exec = (void (*)(struct task *))0x8828a0;
	tp->disp = (void (*)(struct task *))0x882820;
	tp->dest = (void (*)(struct task *))0x7d21b0;
}
