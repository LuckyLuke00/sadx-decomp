#include "decls.h"
void FUN_004e2f70(int param_1, int param_2);

// FUNCTION: SADX 0x0056a200
void FUN_0056a200(struct task *param_1)
{
	struct motionwk *local_8g;
	int local_cg;
	if (param_1 != 0)
	{
		if (param_1->mwp != 0)
		{
			local_8g = param_1->mwp;
			if (local_8g->work.ptr != 0)
			{
				local_cg = (int)local_8g->work.ptr;
				FUN_004e2f70((int)local_8g, local_cg);
			}
		}
	}
}
