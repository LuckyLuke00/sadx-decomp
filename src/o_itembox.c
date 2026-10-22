#include "decls.h"
extern struct NJS_MODEL DAT_05a85e0c;
extern unsigned char DAT_05edd2a4;
void ObjectItemBox(struct task *tp);

// STUB: SADX 0x005dd600
void PutItem_ItemBox(struct NJS_POINT3 *putpos, long putItem)
{
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

// STUB: SADX 0x005de120
void FUN_005de120(struct taskwk *twp)
{
}

// STUB: SADX 0x005de180
void Dead_ItemBox(struct task *tp)
{
}

// FUNCTION: SADX 0x005de1f0
void ef_speed(struct taskwk *twp)
{
	struct colliwk *local_8;

	local_8 = twp->cwp->hit_cwp;
	GetSpeedUpP(*(unsigned char *)((char *)local_8->mytask->twp + 8));
	do
	{
		if (GetPlayerNumber() == 6)
		{
			dsPlay_oneshot(0x51b, 0, 0, 0);
		}
	}
	while (0);
	dsPlay_oneshot(0xb, 0, 0, 0);
}

// FUNCTION: SADX 0x005de260
void ef_5ring(struct taskwk *twp)
{
	AddNumRing(5);
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

// STUB: SADX 0x005de2a0
void ef_10ring(struct taskwk *twp)
{
}

// STUB: SADX 0x005de360
void ef_1up(struct taskwk *twp)
{
}

// STUB: SADX 0x005de3a0
void ef_muteki(struct taskwk *twp)
{
}

// STUB: SADX 0x005de3e0
void ef_baria(struct taskwk *twp)
{
}

// STUB: SADX 0x005de420
void ef_explosion(struct taskwk *twp)
{
}

// STUB: SADX 0x005de470
void ef_th_baria(struct taskwk *twp)
{
}
