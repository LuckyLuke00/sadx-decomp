#include "decls.h"

// STUB: SADX 0x007fa170
void ObjectBeachAttackOrukaSummon(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = (void (*)(struct task *))0x7fa0c0;
}
