#include "decls.h"
static void EmeraldDisplayer(struct task *tp);
extern struct obj *DAT_060b97f4[4];

// FUNCTION: SADX 0x006bf900
static void EmeraldDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y + var1->value.f, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawObjectClipMesh(DAT_060b97f4[var1->smode], 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006bf990
void ObjectPastChaosEmerald(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->smode = *(char *)((char *)var1 + 0x14);
		if (var1->smode < 0 || var1->smode >= 7)
		{
			var1->smode = 0;
		}
		tp->disp = EmeraldDisplayer;
		var1->mode = 1;
		break;
	case 1:
		*(int *)((char *)var1 + 0x18) += 0x80;
		var1->timer.w[0] += 0x100;
		var1->value.f = njSin(var1->timer.w[0]);
		break;
	}
	EmeraldDisplayer(tp);
}
