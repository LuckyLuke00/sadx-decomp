#include "decls.h"
void FUN_0053e5c0(struct task *param_1);

// FUNCTION: SADX 0x0053e580
void MilesSEControle(struct task *tp)
{
	struct task *local_8;
	local_8 = CreateElementalTask(8, 1, FUN_0053e5c0);
	if (local_8)
	{
		local_8->awp->work.ul[0] = 6;
		local_8->awp->work.ul[1] = (long)tp;
	}
}

// FUNCTION: SADX 0x0053e5c0
void FUN_0053e5c0(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	local_8->work.sl[0] = local_8->work.sl[0] - 1;
	if (local_8->work.sl[0] <= 0)
	{
		Serif_Play(local_8->work.sl[1]);
		DestroyTask(param_1);
	}
}

// FUNCTION: SADX 0x0053e610
long IsTailsWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x42)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054fc40
long IsTailsPutting(struct taskwk *twp)
{
	if (twp->mode == 0x16)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x0054fc60
long IsTailsShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x22)
		return 1;
	return 0;
}
