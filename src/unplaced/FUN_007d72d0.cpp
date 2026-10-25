#include "decls.h"

extern int DAT_060cc790[1];

// STUB: SADX 0x007d72d0
void FUN_007d72d0(short param_1)
{
	if ((*(struct task *(*)[1])&DAT_060cc790)[param_1])
	{
		DestroyTask((*(struct task *(*)[1])&DAT_060cc790)[param_1]);
		(*(struct task *(*)[1])&DAT_060cc790)[param_1] = 0;
	}
}
