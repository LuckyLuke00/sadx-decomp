#include "decls.h"
extern struct NJS_TEXLIST texlist_e_sai;
extern struct obj object_rhino;
extern int DAT_05b9d838;
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void njPushMatrix(float *param_1);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void njRotateZ(float *param_1, int param_2);
void njRotateX(float *param_1, unsigned short param_2);
void njRotateY(float *param_1, unsigned short param_2);
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl);
void njPopMatrix(int param_1);

// FUNCTION: SADX 0x00804bc0
void DrawSai(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_e_sai);
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
		late_DrawObjectClip(&object_rhino, 1, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x008052e0
void ObjectWindySetSmoke(struct task *tp)
{
}
