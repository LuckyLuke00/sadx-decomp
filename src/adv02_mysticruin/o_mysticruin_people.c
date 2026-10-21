#include "decls.h"

// FUNCTION: SADX 0x006af220
void mrp_walk_man_end(struct task *task_p)
{
	Free(task_p->awp->work.ptr[0]);
}

// FUNCTION: SADX 0x006afbb0
void mrp_end(struct task *task_p)
{
	Free(*(void **)((char *)task_p->awp + 0x24));
	InputHookDelete(task_p);
}
