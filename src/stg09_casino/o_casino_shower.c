#include "decls.h"

// FUNCTION: SADX 0x00878ef0
void ObjectCasinoShowerEnd(struct task *tp)
{
	if (tp->twp->mode == 2)
	{
		SetInputP(0, 0x29);
	}
}

// STUB: SADX 0x00879400
void ObjectCasinoShower(struct task *tp)
{
}
