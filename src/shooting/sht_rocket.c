#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_shooting0;
extern struct obj object_tr_f_rocket_f_rocket[1];
extern void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x007f0800
void RocketDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(NULL);
		FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		___njSetTexture(&texlist_shooting0);
		late_DrawObjectClipEx(&object_tr_f_rocket_f_rocket[0], 4, 1.0);
		njPopMatrix(1);
	}
}
