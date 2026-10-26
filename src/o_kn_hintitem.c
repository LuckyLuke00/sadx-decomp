#include "decls.h"
extern void (*DAT_00a357e8[3])(struct task *);

// STUB: SADX 0x008e1530
void ObjectKnHintItem(struct task *task_p)
{
}

// FUNCTION: SADX 0x008e15f0
void knhint_exec(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	LoopTaskC(task_p);
	(*DAT_00a357e8[local_8->mode])(task_p);
}

// STUB: SADX 0x008e1630
void knhint_exec_stay(struct task *task_p)
{
}

// STUB: SADX 0x008e1790
void knhint_exec_grgr(struct task *task_p)
{
}

// STUB: SADX 0x008e1870
void knhint_exec_point(struct task *task_p)
{
}
