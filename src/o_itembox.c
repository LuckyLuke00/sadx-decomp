#include "decls.h"
extern struct ITEM_INFOMATION item_info[1];
extern int DAT_05edd2a0;
void ef_random_ring(struct taskwk *twp);
extern struct NJS_POINT3 DAT_009c610c;
extern struct CCL_INFO itembox_colli_info0[1];
void FUN_005ddc80(struct task *param_1);
extern struct NJS_MODEL DAT_05a85e0c;
extern unsigned char DAT_05edd2a4;
void ObjectItemBox(struct task *tp);

// FUNCTION: SADX 0x005dd600
void PutItem_ItemBox(struct NJS_POINT3 *putpos, long putItem)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	local_cg = CreateElementalTask(2, 3, ObjectItemBox);
	local_8g = local_cg->twp;
	local_8g->pos = *putpos;
	local_8g->scl.x = (float)putItem;
	local_cg->dest = Dead_ItemBox;
	local_cg->disp = FUN_005ddc80;
	CCL_Init(local_cg, itembox_colli_info0, 2, 2);
	FUN_005b47c0(local_8g);
	local_8g->scl.z = 0.0f;
	local_cg->mwp = (struct motionwk *)CAlloc(1, 0x23c);
}

// FUNCTION: SADX 0x005dd6a0
void ObjectItemBoxInWater(struct task *tp)
{
	DAT_05edd2a4 = 1;
	ObjectItemBox(tp);
	DAT_05edd2a4 = 0;
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

// FUNCTION: SADX 0x005de0d0
void Draw_Break(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	___dsDrawModel(&DAT_05a85e0c);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005de120
void FUN_005de120(struct taskwk *param_1)
{
	struct NJS_POINT3 local_14;

	local_14 = param_1->pos;
	local_14.y += 5.0f;
	CreateSnow(&local_14, &DAT_009c610c, 1.0f);
}

// STUB: SADX 0x005de180
void Dead_ItemBox(struct task *tp)
{
}

// STUB: SADX 0x005de1f0
void ef_speed(struct taskwk *twp)
{
}

// STUB: SADX 0x005de260
void ef_5ring(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005de2a0
void ef_10ring(struct taskwk *twp)
{
	AddNumRing(0xa);
	UNKNOWN_ONESHOT_MACRO();
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// STUB: SADX 0x005de2e0
void ef_random_ring(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005de360
void ef_1up(struct taskwk *twp)
{
	AddNumPlayer(1);
	UNKNOWN_ONESHOT_MACRO();
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// FUNCTION: SADX 0x005de3a0
void ef_muteki(struct taskwk *twp)
{
	GetInvincibleBodyP(0);
	UNKNOWN_ONESHOT_MACRO();
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// FUNCTION: SADX 0x005de3e0
void ef_baria(struct taskwk *twp)
{
	GetBarrierP(0);
	UNKNOWN_ONESHOT_MACRO();
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// FUNCTION: SADX 0x005de420
void ef_explosion(struct taskwk *twp)
{
	UNKNOWN_ONESHOT_MACRO();
	dsPlay_oneshot(0xb, 0, 0, 0);
	ItemBox_Explosion(&twp->pos);
}

// FUNCTION: SADX 0x005de470
void ef_th_baria(struct taskwk *twp)
{
	GetThunderBarrierP(0);
	UNKNOWN_ONESHOT_MACRO();
	dsPlay_oneshot(0xb, 0, 0, 0);
}
