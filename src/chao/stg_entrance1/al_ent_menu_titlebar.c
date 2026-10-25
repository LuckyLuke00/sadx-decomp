#include "decls.h"
extern void *DAT_05b33018;

// FUNCTION: SADX 0x00474df0
void AL_EntranceMenuLargeTitleBarDisplayerPost(struct task *tp)
{
	AL_EntranceMenuLargeTitleBarDisplayerSub(tp, 1);
}

// FUNCTION: SADX 0x00474e00
void AL_EntranceMenuLargeTitleBarDisplayer(struct task *tp)
{
	AL_EntranceMenuLargeTitleBarDisplayerSub(tp, 0);
	AL_ENT_DelayedTaskAdd(tp, AL_EntranceMenuLargeTitleBarDisplayerPost);
}

// FUNCTION: SADX 0x00474e20
void AL_EntranceMenuLargeTitleBarDestructor(struct task *tp)
{
	*(int *)((char *)DAT_05b33018 + 0xf4) = 0;
}

// FUNCTION: SADX 0x004750e0
void CreateLargeTitleBar(struct task *tp, unsigned short timer)
{
	if (*(struct task **)((char *)DAT_05b33018 + 0xf4) == 0)
	{
		struct task *var1;

		var1 = CreateChildTask(2, AL_EntranceMenuLargeTitleBarExecutor, tp);
		var1->disp = AL_EntranceMenuLargeTitleBarDisplayer;
		var1->dest = AL_EntranceMenuLargeTitleBarDestructor;
		var1->twp->wtimer = timer;
		*(struct task **)((char *)DAT_05b33018 + 0xf4) = var1;
	}
}

// FUNCTION: SADX 0x00475550
void AL_EntranceMenuSmallTitleBarDestructor(struct task *tp)
{
	*(int *)((char *)DAT_05b33018 + 0xf8) = 0;
}

// FUNCTION: SADX 0x004757d0
void CreateSmallTitleBar(struct task *tp, unsigned short timer)
{
	if (*(struct task **)((char *)DAT_05b33018 + 0xf8) == 0)
	{
		struct task *var1;

		var1 = CreateChildTask(2, AL_EntranceMenuSmallTitleBarExecutor, tp);
		var1->disp = AL_EntranceMenuSmallTitleBarDisplayer;
		var1->dest = AL_EntranceMenuSmallTitleBarDestructor;
		var1->twp->wtimer = timer;
		*(struct task **)((char *)DAT_05b33018 + 0xf8) = var1;
	}
}
