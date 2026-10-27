#include "decls.h"
void WireClothWindDisplayer(struct task *tp);
extern int DAT_05b3e0d0;
extern int DAT_05b9d838;
extern struct obj object_wvobj_ha_red_ha_red[1];

// FUNCTION: SADX 0x0080bb70
void WireClothWindDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b3e0d0 < 2)
	{
		if (DAT_05b9d838 == 0)
		{
			if (var1->value.f > -50.0f)
			{
				SetObjectTexture();
				njPushMatrix(0);
				FUN_0067d830(0, var1->pos.x, var1->pos.y + var1->value.f, var1->pos.z);
				if (var1->ang.y)
				{
					njRotateY(0, var1->ang.y);
				}
				FUN_0067d2d0(0, var1->scl.x, 1.0f, var1->scl.x);
				late_DrawObjectClip(object_wvobj_ha_red_ha_red, 0, var1->scl.x > 1.0f ? var1->scl.x : 1.0f);
				njPopMatrix(1);
			}
		}
	}
}
