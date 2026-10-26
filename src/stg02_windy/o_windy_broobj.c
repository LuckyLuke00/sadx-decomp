#include "decls.h"
extern struct NJS_MODEL *DAT_03b26f48;
extern struct NJS_MODEL *DAT_03b273a0;
extern struct NJS_MODEL *DAT_03b27828;

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
