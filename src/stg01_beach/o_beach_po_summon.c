#include "decls.h"
static void Exec(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x007f9e70
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007f9ee0
void ObjectBeachPathOrukaSummon(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = Exec;
}
