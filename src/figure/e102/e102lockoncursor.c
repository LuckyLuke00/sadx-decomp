#include "decls.h"
void FUN_005e5770(struct task *param_1);

// FUNCTION: SADX 0x005e5750
struct task *GetE102LockCsTaskPointer(struct task *beam_tp)
{
	if (beam_tp == NULL)
		return NULL;
	return (struct task *)beam_tp->twp->value.ptr;
}

// STUB: SADX 0x005e5860
void E102LockOnCursor_dis(struct task *tp)
{
}

// FUNCTION: SADX 0x005e5bb0
void E102KillCursorOnly(struct task *tp)
{
	struct motionwk *local_8;

	if (tp == NULL)
	{
		return;
	}
	local_8 = tp->mwp;
	if (local_8 == NULL)
	{
		return;
	}
	if (*(void **)((char *)local_8 + 0x40) == NULL)
	{
		return;
	}
	if (*(void **)((char *)*(void **)((char *)local_8 + 0x40) + 0x20) != NULL)
	{
		*(short *)((char *)*(void **)((char *)*(void **)((char *)local_8 + 0x40) + 0x20) + 4) |= 0x100;
	}
	FUN_005e5770(tp);
}
