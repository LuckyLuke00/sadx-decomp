#include "decls.h"
float FUN_00500c70(float param_1, float param_2, float param_3);
void egm2_leg_hide_set();
extern unsigned char DAT_060b9b44;

// STUB: SADX 0x006c8580
void egm2_leg_model_get(struct LegModel *legmodel, struct obj *obj, long root)
{
}

// FUNCTION: SADX 0x006c8620
void leg_disp(struct LegModel *legmodel)
{
	do
	{
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, *(float *)legmodel, *(float *)((char *)legmodel + 4), *(float *)((char *)legmodel + 8));
		if (*(int *)((char *)legmodel + 0x14) != 0)
		{
			njRotateZ(NULL, *(unsigned short *)((char *)legmodel + 0x14));
		}
		if (*(int *)((char *)legmodel + 0x10) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)legmodel + 0x10));
		}
		if (*(int *)((char *)legmodel + 0xc) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)legmodel + 0xc));
		}
		FUN_0067d2d0((float *)0, *(float *)((char *)legmodel + 0x18), *(float *)((char *)legmodel + 0x1c), *(float *)((char *)legmodel + 0x20));
		struct NJS_MODEL *var1 = (struct NJS_MODEL *)*(int *)((char *)legmodel + 0x24);
		if (var1 != (struct NJS_MODEL *)0)
		{
			ds_DrawModelClip(var1, FUN_00500c70(*(float *)((char *)legmodel + 0x18), *(float *)((char *)legmodel + 0x1c), *(float *)((char *)legmodel + 0x20)));
		}
		if (*(int *)((char *)legmodel + 0x28) != 0)
		{
			leg_disp((struct LegModel *)*(int *)((char *)legmodel + 0x28));
		}
		njPopMatrix(1);
		legmodel = (struct LegModel *)*(int *)((char *)legmodel + 0x2c);
	}
	while (legmodel != (struct LegModel *)0);
}

// STUB: SADX 0x006c8b40
void egm2_obj_eval_hide_set(struct obj *obj, long root, long hide)
{
}

// FUNCTION: SADX 0x006c8dc0
long Egm2LegHokanCheck()
{
	return DAT_060b9b44 == 3;
}

// STUB: SADX 0x006c8f50
void egm2_leg_hide_set()
{
}

// STUB: SADX 0x006c9930
void Egm2LegHokanCalc()
{
}
