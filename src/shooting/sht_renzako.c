#include "decls.h"
extern struct NJS_ACTION action_stene_s_renzako[1];

// FUNCTION: SADX 0x007f0bb0
void RenzakoDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		if (StageEventCheck() == 0)
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
			late_ActionClipEx(&action_stene_s_renzako[0], var1->value.f, 4, 1.0);
			njPopMatrix(1);
		}
	}
}
