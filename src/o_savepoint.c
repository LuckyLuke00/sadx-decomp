#include "decls.h"

// FUNCTION: SADX 0x005a58c0
void savepointExit(struct task *tp)
{
	if (tp->awp->work.ptr[0] != 0)
	{
		Free(tp->awp->work.ptr[0]);
		tp->awp->work.ptr[0] = 0;
	}
}

// STUB: SADX 0x005a5a20
void *FUN_005a5a20()
{
	return (void *)0;
}
