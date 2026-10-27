#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00803ad0
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00803bf0
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00803db0
void ObjectBeachWatertube(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// STUB: SADX 0x00803dd0
void CreateBeachWatertube(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl)
{
}
