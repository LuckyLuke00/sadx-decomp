#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_ARGB DAT_02671d94;

// FUNCTION: SADX 0x005d3b80
void FUN_005d3b80(struct task *param_1)
{
	struct taskwk *local_8g;
	int local_cg;
	local_8g = param_1->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	___njSetConstantMaterial(&DAT_02671d94);
	___njSetTexture(&texlist_e102_beam);
	njPushMatrix(0);
	local_cg = (*(unsigned short *)((char *)local_8g + 6) & 0x200) != 0;
	njTranslateV(0, &local_8g->pos);
	sprite_e102_flash.sy = *(float *)((char *)local_8g + 8);
	sprite_e102_flash.sx = sprite_e102_flash.sy;
	late_DrawSprite3D(&sprite_e102_flash, local_cg, 0x30, 4);
	ResetMaterial();
	njPopMatrix(1);
}
