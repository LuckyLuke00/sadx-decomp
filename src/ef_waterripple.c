#include "decls.h"
static void Disp(struct task *tp);

// FUNCTION: SADX 0x00570970
void ObjectWaterripple(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	*(char *)local_8 = 0;
	tp->exec = _Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
}

#pragma optimize("", off)
// STUB: SADX 0x00570a90
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)
