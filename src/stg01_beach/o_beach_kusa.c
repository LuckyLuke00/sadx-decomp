#include "decls.h"
extern struct taskwk *DAT_05b42a7c;
extern struct obj object_seaobj_kusa7_kusa7[1];
float FUN_007f6280(struct NJS_POINT3 *param_1);
extern int DAT_05b9d838;

// FUNCTION: SADX 0x007fbfc0
void DrawKusa(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if (DAT_05b42a7c != 0)
		{
			float var2 = FUN_007f6280(&var1->pos);

			if (var2 < 10000.0f)
			{
				late_DrawObjectClipMesh((struct obj *)&object_seaobj_kusa7_kusa7, 1, 1.0f);
				njPopMatrix(1);
				return;
			}
		}
		late_DrawObjectClip((struct obj *)&object_seaobj_kusa7_kusa7, 1, 1.0f);
		njPopMatrix(1);
	}
}
