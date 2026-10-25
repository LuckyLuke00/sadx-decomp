#include "decls.h"
extern struct fe_dynamicswk default_dynamicswk;

// FUNCTION: SADX 0x008a2020
void FEGG_TaskActGravity(struct taskwk *twp, struct motionwk *mwp)
{
	mwp->acc.y -= 0.07999999821186066f;
}

// STUB: SADX 0x008a2040
void FEGG_TaskMove(struct taskwk *twp, struct motionwk *mwp)
{
}

// FUNCTION: SADX 0x008a2170
void FEGG_SetDynamicsWork(struct task *tp, struct fe_dynamicswk *dwp)
{
	struct fe_dynamicswk **var1;

	var1 = (struct fe_dynamicswk **)tp->mwp;
	if (dwp == NULL)
	{
		*var1 = &default_dynamicswk;
	}
	else
	{
		*var1 = dwp;
	}
}
