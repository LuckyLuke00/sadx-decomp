#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_ARGB DAT_02671d74;

// FUNCTION: SADX 0x005d3470
void E102BeamDisplay(struct task *tp)
{
	struct taskwk *local_8g;
	int local_cg;
	local_8g = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetConstantMaterial(&DAT_02671d74);
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	njPushMatrix(0);
	local_cg = (local_8g->wtimer & 0x200) != 0;
	njTranslateV(0, &local_8g->pos);
	___njSetTexture(&texlist_e102_beam);
	late_DrawSprite3D(&sprite_e102_beam, local_cg, 0x30, 4);
	ResetMaterial();
	njPopMatrix(1);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x005d3530
void E102BeamDestruct(struct task *tp)
{
}

// STUB: SADX 0x005d35b0
void E102BeamAto(struct task *tp)
{
}

// FUNCTION: SADX 0x005d3950
void SetE102BeamNoHorming(struct task *tp, struct NJS_POINT3 *vec)
{
	tp->twp->mode = 2;
	tp->twp->value.l = 0;
	if (vec != (struct NJS_POINT3 *)0)
	{
		tp->mwp->spd = *vec;
	}
}

// STUB: SADX 0x005d3b00
void FUN_005d3b00(struct task *tp)
{
}
