#include "decls.h"
#include <stdlib.h>

// FUNCTION: SADX 0x007062a0
static void exec_Lightning(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct NJS_POINT3 local_14;
	struct NJS_POINT3 *local_1c;
	float local_18;

	if (--var1->wtimer == 0)
	{
		FreeTask(pTask);
		return;
	}
	if (DAT_05b9d838 == 0)
	{
		local_18 = (float)(rand() * 0.000030517578125);
		if (local_18 < 0.5f)
		{
			local_1c = (struct NJS_POINT3 *)var1->value.ptr;
			local_14.x = local_1c->x;
			local_14.y = local_1c->y;
			local_14.z = local_1c->z;
			local_18 = (float)(rand() * 0.000030517578125);
			local_14.x += local_18 * 10.0 - 5.0;
			local_18 = (float)(rand() * 0.000030517578125);
			local_14.y += local_18 * 10.0 - 5.0;
			local_18 = (float)(rand() * 0.000030517578125);
			local_14.z += local_18 * 10.0 - 5.0;
			CreateLightning(&local_14, 1.0f);
		}
	}
}

// FUNCTION: SADX 0x007063e0
void breakLightning(struct task *pTask)
{
	struct task *local_4 = CreateElementalTask(2, 4, exec_Lightning);
	if (local_4 != NULL)
	{
		struct taskwk *local_8 = local_4->twp;
		local_8->wtimer = 60;
		local_8->value.ptr = pTask;
		dsPlay_oneshot(156, 0, 0, 0);
	}
}
