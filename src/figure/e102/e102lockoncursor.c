#include "decls.h"
extern int DAT_05b9d838;
void DispMultiDigitDisplay(struct task *tp);
void FUN_005e5770(struct task *param_1);

// STUB: SADX 0x005e5440
void E102LockOnCursor_dest(struct task *tp)
{
}

// FUNCTION: SADX 0x005e54f0
void DispMultiDigit(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	switch (local_8->mode)
	{
	case 0:
		tp->disp = DispMultiDigitDisplay;
		local_8->mode = 1;
		break;
	}
	DispMultiDigitDisplay(tp);
}

// STUB: SADX 0x005e5540
void DispMultiDigitDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x005e5750
struct task *GetE102LockCsTaskPointer(struct task *beam_tp)
{
	if (beam_tp == NULL)
		return NULL;
	return (struct task *)beam_tp->twp->value.ptr;
}

#pragma optimize("", off)
// STUB: SADX 0x005e5770
void FUN_005e5770(struct task *param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005e5860
void E102LockOnCursor_dis(struct task *tp)
{
	struct taskwk *local_cg;
	struct anywk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->awp;
	if (local_cg->timer.l >= 0x3c)
	{
		FreeTask(tp);
	}
	else
	{
		local_cg->timer.l += 1;
		*(int *)((char *)local_8g + 0x24) += 0x200;
		*(int *)((char *)local_8g + 0x28) += 0x300;
		tp->disp = E102LockOnCursor_dis_Disp;
		E102LockOnCursor_dis_Disp(tp);
	}
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
