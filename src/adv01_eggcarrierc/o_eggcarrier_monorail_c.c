#include "decls.h"

// STUB: SADX 0x006a2520
void MonorailAnimater(struct task *tp)
{
}

// STUB: SADX 0x006a2880
void MonorailCarDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x006a2a80
void MonorailDestructor(struct task *tp)
{
	FreeTaskC(tp);
	if (tp->mwp != NULL)
	{
		if (tp->mwp->ang_spd.x != 0)
		{
			Free((void *)tp->mwp->ang_spd.x);
		}
		Free(tp->mwp);
		tp->mwp = NULL;
	}
}
