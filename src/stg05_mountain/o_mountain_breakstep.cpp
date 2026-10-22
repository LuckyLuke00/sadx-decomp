#include "decls.h"

// FUNCTION: SADX 0x008310d0
void DesertAChildTask(struct task *p_task)
{
	Free(p_task->twp->value.ptr);
}

// STUB: SADX 0x00831380
void DesertATask(struct task *tp)
{
}
