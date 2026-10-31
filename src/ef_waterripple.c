#include "decls.h"
void ObjectWaterripple(struct task *tp);
static void Disp(struct task *tp);

// STUB: SADX 0x005708f0
void CreateWaterripple(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl)
{
}

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

// STUB: SADX 0x00570a90
static void Disp(struct task *tp)
{
}
