#include "decls.h"
extern struct CCL_INFO DAT_0303f1ec;

// STUB: SADX 0x007d7910
void ev_frog_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007d7950
struct task *SetEventFrog()
{
	struct task *var1 = CreateElementalTask(2, 5, ev_frog_exec);
	SetEventWork(var1->twp);
	CCL_Init(var1, &DAT_0303f1ec, 1, 4);
	return var1;
}
