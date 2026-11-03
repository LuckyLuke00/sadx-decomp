#include "decls.h"
extern struct ITEM_INFOMATION item_info[1];
extern int DAT_05edd2a0;

// FUNCTION: SADX 0x005dd9a0
void FUN_005dd9a0(void *param_1)
{
	*(float *)((char *)param_1 + 0x34) = *(float *)((char *)param_1 + 0x34) + 0.10999999940395355;
	if (5.0 <= *(float *)((char *)param_1 + 0x34))
	{
		*(char *)param_1 = 2;
		*(float *)((char *)param_1 + 0x34) = 1.0;
	}
}

// FUNCTION: SADX 0x005dd9e0
void FUN_005dd9e0(struct task *param_1)
{
	struct taskwk *local_cg;
	struct colliwk *local_8g;

	local_cg = param_1->twp;
	local_8g = local_cg->cwp->hit_cwp;
	if (CheckEditMode() == 0)
	{
		if (DAT_05baf368[0] == 0)
			return;
		if ((local_cg->cwp->flag & 1) != 0)
		{
			if (local_8g->id == 0 || local_8g->id == 1)
			{
				if (local_cg->cwp->my_num == 1)
				{
					local_cg->mode = 3;
					if (local_cg->cwp->hit_cwp->mytask == GetPlayerTaskPointer(0) && (DAT_05baf368[0]->flag & 1) == 0)
						SetVelocityP(0, 0.0f, 2.0f, 0.0f);
					else if (local_cg->cwp->hit_cwp->mytask == GetPlayerTaskPointer(1) && (DAT_05baf368[0]->flag & 1) == 0)
						SetVelocityP(1, 0.0f, 2.0f, 0.0f);
				}
				if ((local_cg->flag & 4) != 0)
					local_cg->mode = 3;
				if (local_cg->mode == 3 && item_info[DAT_05edd2a0].effect_func != 0)
				{
					if (local_cg->cwp->hit_cwp->mytask == GetPlayerTaskPointer(0)
						|| GetPlayerNumber() == 6
						|| GetPlayerNumber() == 7
						|| GetPlayerNumber() == 0
						|| (GetPlayerCharacterName(1) == 2 && GetPlayerCharacterName(0) == 0)
						|| (GetPlayerCharacterName(0) == 2 && GetPlayerCharacterName(1) != 0))
					{
						item_info[DAT_05edd2a0].effect_func(local_cg);
						EntryItemBoxPanel(DAT_05edd2a0);
					}
				}
			}
		}
		EntryColliList(local_cg);
		local_cg->scl.y += 3.0;
	}
}

// FUNCTION: SADX 0x005ddbf0
void FUN_005ddbf0(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (param_1->ocp != 0)
	{
		if (FUN_00551570((int)param_1) != 0)
		{
			local_8->mode = local_8->mode;
		}
		else
		{
			FUN_00551530((int)param_1);
			FUN_005de120(local_8);
		}
	}
	else
	{
		FUN_005de120(local_8);
	}
	FUN_005e5770(param_1);
	FUN_004da910((int)local_8);
	CCL_Init(param_1, itembox_colli_info1, 2, 4);
	local_8->mode = 4;
}

// STUB: SADX 0x005ddc80
void FUN_005ddc80(struct task *param_1)
{
}

// STUB: SADX 0x005ddea0
void FUN_005ddea0(struct task *param_1)
{
}
