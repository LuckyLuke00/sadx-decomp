#include "decls.h"
extern unsigned char DAT_05bafce4;

// FUNCTION: SADX 0x00685610
void ssp_walk_man_eveidle(struct task *task_p)
{
	if (EV_CheckCansel() == 0)
	{
		FreeTaskC(task_p);
		ssp_walk_man_1st(task_p);
		task_p->exec = ssp_walk_man;
	}
	else if (DAT_05bafce4 != 0)
	{
		LoopTaskC(task_p);
	}
}

// FUNCTION: SADX 0x00685650
void ssp_walk_man(struct task *task_p)
{
	if (EV_CheckCansel())
	{
		task_p->exec = ssp_walk_man_eveidle;
		return;
	}
	LoopTaskC(task_p);
}
