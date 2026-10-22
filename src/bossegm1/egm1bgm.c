#include "decls.h"

// FUNCTION: SADX 0x006c2060
void egm1_bgm_exec(struct task *tp)
{
	int local_8;
	local_8 = tp->awp->work.ul[0];
	tp->awp->work.ul[0] = local_8 + 1;
	if (local_8 > 1)
	{
		BGM_Play(8);
		FreeTask(tp);
	}
}

// FUNCTION: SADX 0x006c2090
void SetEgm1Bgm()
{
	struct task *var1;
	ADXTaskInit();
	var1 = CreateElementalTask(0, 4, egm1_bgm_exec);
	if (var1 != 0)
	{
		var1->awp = (struct anywk *)CAlloc(1, 4);
		*(int *)var1->awp = 0;
	}
}
