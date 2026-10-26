#include "decls.h"
static void Exec(struct task *tp);
void FUN_007d21b0(...);

#pragma optimize("", off)
// STUB: SADX 0x0049aa30
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0049ab20
void ObjectMiTimer(struct task *tp)
{
	tp->exec = Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
