#include "decls.h"

// FUNCTION: SADX 0x007f9ee0
void ObjectBeachPathOrukaSummon(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = (void (*)(struct task *))0x7f9e70;
}
