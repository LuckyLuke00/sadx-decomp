#include "decls.h"
extern unsigned char DAT_05bafce4;

// STUB: SADX 0x006be6e0
void pastp_walk_end(struct task *task_p)
{
}

// STUB: SADX 0x006becf0
void pastp_exec_eveidle(struct task *task_p)
{
}

// FUNCTION: SADX 0x006bf090
void pastp_walk_man_eveidle(struct task *task_p)
{
	if (EV_CheckCansel() == 0)
	{
		pastp_walk_man_1st(task_p);
		task_p->exec = pastp_walk_man;
	}
	else if (DAT_05bafce4 != 0)
	{
		LoopTaskC(task_p);
	}
}

// FUNCTION: SADX 0x006bf0c0
void pastp_walk_man(struct task *task_p)
{
	if (EV_CheckCansel())
	{
		task_p->exec = pastp_walk_man_eveidle;
		return;
	}
	LoopTaskC(task_p);
}
