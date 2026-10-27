#include "decls.h"
static void PieceDisp(struct task *tp);
extern struct NJS_MODEL *DAT_03b26f48;
extern struct NJS_MODEL *DAT_03b273a0;
extern struct NJS_MODEL *DAT_03b27828;

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
