#include "decls.h"
static void Exec(struct task *tp);

// STUB: SADX 0x007fa0c0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007fa170
void ObjectBeachAttackOrukaSummon(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = Exec;
}
