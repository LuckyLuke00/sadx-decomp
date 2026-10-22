#include "decls.h"
void FUN_007d21b0(void *param_1);

// FUNCTION: SADX 0x006c09a0
void ObjectPastPyramidStairs(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->disp = PyramidStairsDisplayer;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->twp->mode = 1;
	}
	PyramidStairsDisplayer(tp);
}

// FUNCTION: SADX 0x006c09d0
void ObjectPastBigStairs(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		tp->disp = BigStairsDisplayer;
		tp->dest = (void (*)(struct task *))FUN_007d21b0;
		tp->twp->mode = 1;
	}
	BigStairsDisplayer(tp);
}
