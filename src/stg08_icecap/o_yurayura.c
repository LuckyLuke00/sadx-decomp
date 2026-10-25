#include "decls.h"
static void Normal(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x0085e000
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0085e150
void ObjectYuraYura(struct task *tp)
{
	tp->twp->counter.l = 0;
	tp->twp->btimer = 0;
	tp->exec = Normal;
}
