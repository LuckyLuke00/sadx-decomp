#include "decls.h"

// STUB: SADX 0x007e1f40
void EV_OInitialize(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x007e1f60
void EV_ODestruct(struct taskwk *twp)
{
	struct _eventobjwk *var1 = (struct _eventobjwk *)twp->value.ptr;
	*(unsigned short *)var1 = 14;
	if (*(void **)((char *)var1 + 0x20) != 0)
	{
		EV_OSetMotion((struct _emtnjvwk *)var1);
	}
	*(unsigned short *)((char *)var1 + 2) = 2;
	if (*(void **)((char *)var1 + 0x1c) != 0)
	{
		EV_OJoinVertexes(twp, var1);
	}
	Free(var1);
	twp->value.ptr = 0;
}
