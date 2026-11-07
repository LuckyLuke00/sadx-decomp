#include "decls.h"
static void EmeraldDisplayer(struct task *tp);

// FUNCTION: SADX 0x006bfa00
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
	late_DrawObjectClipMesh(*(struct obj **)DAT_060eeaa4, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006bfa90
void ObjectPastMasterEmerald(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		CCL_Init(tp, &cinfo_emerald[0], 1, 4);
		tp->disp = EmeraldDisplayer;
		var1->mode = 1;
		break;
	case 1:
		var1->ang.y += 0x80;
		var1->timer.w[0] += 0x100;
		var1->value.f = njSin(var1->timer.w[0]);
		break;
	}
	EntryColliList(var1);
	EmeraldDisplayer(tp);
}
