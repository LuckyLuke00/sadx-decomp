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
		___njSetTexture(&texlist_shooting0);
		late_DrawObjectClipEx(&object_tr_f_rocket_f_rocket[0], 4, 1.0);
		njPopMatrix(1);
	}
}
