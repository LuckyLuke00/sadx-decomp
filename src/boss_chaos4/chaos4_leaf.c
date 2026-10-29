#include "decls.h"
extern struct NJS_ACTION action_c4_s_skusa[1];
extern struct NJS_TEXLIST texlist_chaos4_object;
extern struct NJS_ACTION action_c4_s_skusa[];
void Tmit_MaterialInit();
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void late_ActionClipMS(NJS_ACTION *action, float frame, int flgs, float clipScl);
extern int DAT_05b9d838;
extern int DAT_05b3df4c;
extern float DAT_05b3df40;

// FUNCTION: SADX 0x006f14f0
void Dsp_Leaf(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct anywk *var2 = pTask->awp;
	if (DAT_05b9d838 == 0)
	{
		Tmit_MaterialInit();
		___njSetTexture(&texlist_chaos4_object);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (DAT_05b3df4c != 0)
		{
			if (*(short *)((char *)var2 + 0xe) > 0)
			{
				DAT_05b3df40 = -17952.0f;
			}
		}
		late_DrawObjectClipMS((struct obj *)&object_c4_nc_s_asiba_nc_s_asiba, 1, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x006f16a0
int FUN_006f16a0(float *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x006f1750
void Dsp_small_leaf(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	if (DAT_05b9d838 == 0)
	{
		Tmit_MaterialInit();
		___njSetTexture(&texlist_chaos4_object);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		late_ActionClipMS((struct NJS_ACTION *)&action_c4_s_skusa, var1->counter.f, 1, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x006f1b20
void Exe_small_leaf(struct task *pTask)
{
}
