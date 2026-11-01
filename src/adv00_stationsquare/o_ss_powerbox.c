#include "decls.h"

// GLOBAL: SADX 0x026dcd30
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x00686960
void ObjectSSPowerbox(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->ang.x = 0;
	var1->ang.z = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
	}
	tp->exec = FUN_00686920;
	tp->disp = FUN_006868b0;
}
