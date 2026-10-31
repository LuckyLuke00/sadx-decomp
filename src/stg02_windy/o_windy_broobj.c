#include "decls.h"

// GLOBAL: SADX 0x03b75a30
static struct CCL_INFO c_info01[2];

static void Exec(struct task *tp);
static void Disp(struct task *tp);
static void PieceDisp(struct task *tp);
extern struct NJS_MODEL *DAT_03b26f48;
extern struct NJS_MODEL *DAT_03b273a0;
extern struct NJS_MODEL *DAT_03b27828;

// STUB: SADX 0x00809340
static void Disp(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00809490
static void PieceDisp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00809540
void DispCube(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 10.0f))
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		switch ((int)var1->scl.x)
		{
			case 0:
				late_DrawModelClip(DAT_03b27828, 1, 1.0f);
				break;
			case 1:
				late_DrawModelClip(DAT_03b273a0, 1, 1.0f);
				break;
			case 2:
				late_DrawModelClip(DAT_03b26f48, 1, 1.0f);
				break;
		}
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00809620
void ColliOnly(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		CCL_Init(tp, &c_info_dummy[0], 1, 4);
		break;
	case 1:
		EntryColliList(var1);
		break;
	}
}

// FUNCTION: SADX 0x00809660
void PieceExec(struct task *tp)
{
	struct motionwk *var1;
	struct taskwk *var2;
	var2 = tp->twp;
	var1 = tp->mwp;
	var2->pos.x = var1->spd.x + var2->pos.x;
	var2->pos.y = var1->spd.y + var2->pos.y;
	var2->pos.z = var1->spd.z + var2->pos.z;
	var1->spd.y = var1->spd.y - 0.10000000149011612;
	*(int *)((char *)var2 + 0x18) = *(int *)((char *)var2 + 0x18) + *(int *)((char *)var1 + 0x2c);
	*(int *)((char *)var2 + 0x14) = *(int *)((char *)var2 + 0x14) + *(int *)((char *)var1 + 0x28);
	if (var2->wtimer > 0x14)
	{
		var2->value.f = var2->value.f - 0.019999999552965164;
	}
	else
	{
		var2->wtimer = var2->wtimer + 1;
	}
	PieceDisp(tp);
}

// STUB: SADX 0x00809b40
void ObjectWindyBrokenCubes(struct task *tp)
{
}

// STUB: SADX 0x00809c30
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00809da0
void ObjectWindyBrokenObj(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	EnemyInitialize(tp, var1);
	var1->counter.f = 0.0f;
	var1->mode = 0;
	var1->wtimer = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &c_info01[1], 1, 2);
	}
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = FUN_00850d10;
}
