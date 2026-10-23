#include "decls.h"
extern struct task *DAT_060cca6c;

// FUNCTION: SADX 0x007da530
void frog_exec(struct task *tp)
{
	tp->twp->ang.y = (tp->twp->ang.y + 0x200) & 0xffff;
	frog_disp(tp);
}

// FUNCTION: SADX 0x007da5a0
void frog_delete()
{
	if (DAT_060cca6c)
	{
		FreeTask(DAT_060cca6c);
		DAT_060cca6c = 0;
	}
}
