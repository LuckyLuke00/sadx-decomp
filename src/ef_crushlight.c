#include "decls.h"

// FUNCTION: SADX 0x008c23b0
void execDeathCrushLight(struct task *pTask)
{
	struct anywk *local_8;
	local_8 = pTask->awp;
	rotate((struct CRUSHLIGHT_WK *)local_8);
	local_8->work.f[3] = local_8->work.f[3] - 0.1f;
	if (local_8->work.f[3] <= 0.0f)
	{
		local_8->work.f[3] = 0.0f;
		FreeTask(pTask);
	}
	dispCrushLight(pTask);
}
