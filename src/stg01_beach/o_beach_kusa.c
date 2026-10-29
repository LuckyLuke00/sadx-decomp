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
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
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
