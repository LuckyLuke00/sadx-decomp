#include "decls.h"
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
	*(float *)((char *)local_8g + 0x34) = 0.0f;
	local_cg->mwp = (struct motionwk *)CAlloc(1, 0x23c);
}

// FUNCTION: SADX 0x005dd6a0
void ObjectItemBoxInWater(struct task *tp)
{
	DAT_05edd2a4 = 1;
	ObjectItemBox(tp);
	DAT_05edd2a4 = 0;
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

// STUB: SADX 0x005de2a0
void ef_10ring(struct taskwk *twp)
{
	AddNumRing(0xa);
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51a, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// STUB: SADX 0x005de2e0
void ef_random_ring(struct taskwk *twp)
{
}

// STUB: SADX 0x005de360
void ef_1up(struct taskwk *twp)
{
	AddNumPlayer(1);
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51a, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// STUB: SADX 0x005de3a0
void ef_muteki(struct taskwk *twp)
{
	GetInvincibleBodyP(0);
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51a, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// STUB: SADX 0x005de3e0
void ef_baria(struct taskwk *twp)
{
	GetBarrierP(0);
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51a, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// STUB: SADX 0x005de420
void ef_explosion(struct taskwk *twp)
{
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51a, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
	ItemBox_Explosion(&twp->pos);
}

// STUB: SADX 0x005de470
void ef_th_baria(struct taskwk *twp)
{
	GetThunderBarrierP(0);
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51a, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
}
