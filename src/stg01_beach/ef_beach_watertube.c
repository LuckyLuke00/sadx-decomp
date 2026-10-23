#include "decls.h"

// FUNCTION: SADX 0x00803db0
void ObjectBeachWatertube(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = (void (*)(struct task *))0x803bf0;
	tp->disp = (void (*)(struct task *))0x803ad0;
	tp->dest = (void (*)(struct task *))0x7d21b0;
}

// STUB: SADX 0x00803dd0
void CreateBeachWatertube(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl)
{
}
