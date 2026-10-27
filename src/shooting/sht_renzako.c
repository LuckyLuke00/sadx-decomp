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
			njPushMatrix((float *)0);
			FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x18) != 0)
			{
				njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
			}
			___njSetTexture(&texlist_shooting0);
			late_ActionClipEx(&action_stene_s_renzako[0], var1->value.f, 4, 1.0);
			njPopMatrix(1);
		}
	}
}
