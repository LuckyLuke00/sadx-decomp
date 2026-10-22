#include "decls.h"
extern void (*DAT_0099613c[4])(struct task *);

// FUNCTION: SADX 0x005abbc0
void FUN_005abbc0(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	if (FUN_004c39c0(param_1) == 0)
	{
		LoopTaskC(param_1);
	}
	DAT_0099613c[local_8->mode](param_1);
	relbox_end(param_1);
	EntryColliList(local_8);
}
