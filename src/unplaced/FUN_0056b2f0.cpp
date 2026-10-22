#include "decls.h"
void FUN_0056a200(struct task *param_1);
void FUN_0056b6d0(struct task *param_1);
void FUN_0056b920(struct task *param_1);

// FUNCTION: SADX 0x0056b2f0
void FUN_0056b2f0(struct task **param_1)
{
	if (*param_1 != 0)
	{
		FreeTask(*param_1);
	}
	*param_1 = 0;
}

// FUNCTION: SADX 0x0056b320
void FUN_0056b320(struct task *param_1)
{
	if (param_1)
	{
		FUN_0056b6d0(param_1);
		EV_ClrPath(param_1);
		FUN_0056b920(param_1);
		EV_MoveFree(param_1);
		EV_ClrFace(param_1);
	}
}

// FUNCTION: SADX 0x0056b370
void FUN_0056b370(struct task *param_1, float param_2, float param_3, float param_4)
{
	struct taskwk *local_8;

	if (param_1 != 0)
	{
		local_8 = param_1->twp;
		FUN_0056a200(param_1);
		local_8->pos.x = param_2;
		local_8->pos.y = param_3;
		local_8->pos.z = param_4;
		if (local_8->cwp != 0)
		{
			if (local_8->cwp->id == 0)
			{
				SetPlayerPosition(*(unsigned char *)((char *)local_8 + 8), 0, &local_8->pos, 0);
			}
		}
	}
}

// FUNCTION: SADX 0x0056b3e0
void FUN_0056b3e0(struct task *param_1, long param_2, long param_3, long param_4)
{
	struct taskwk *local_8;
	if (param_1 != 0)
	{
		local_8 = param_1->twp;
		FUN_0056a200(param_1);
		local_8->ang.x = param_2;
		local_8->ang.y = 0x4000 - param_3;
		local_8->ang.z = param_4;
	}
}
