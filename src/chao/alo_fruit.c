#include "decls.h"

// STUB: SADX 0x004478f0
long ALO_GetFruitKind(struct task *tp)
{
	return *(long *)&tp->twp->ang;
}
