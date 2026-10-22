#include "decls.h"

// FUNCTION: SADX 0x00478a00
void AloG00FountainDest(struct task *tp)
{
	tp->disp = 0;
}

// FUNCTION: SADX 0x00478a80
void AloG00FountainExec(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->disp = AloG00FountainDisp;
		tp->dest = AloG00FountainDest;
		tp->twp->mode = 1;
	}
	AloG00FountainDisp(tp);
}
