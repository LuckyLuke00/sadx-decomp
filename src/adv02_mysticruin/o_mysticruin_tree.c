#include "decls.h"
extern int DAT_05b9d838;
extern float DAT_05b3df40;
extern struct obj *DAT_060eea9c;
long SetObjectTexture();
void njPushMatrix(float *param_1);
void njTranslateV(float *param_1, struct NJS_POINT3 *param_2);
void njRotateZXY(long param_1, long param_2, long param_3, long param_4);
void late_DrawObjectClipEx(struct obj *obj, int flgs, float clipScl);
void njPopMatrix(int param_1);

// FUNCTION: SADX 0x006b2ca0
void TreeDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njRotateZXY(0, var1->ang.x, var1->ang.y, var1->ang.z);
	DAT_05b3df40 = -37952.0f;
	late_DrawObjectClipEx(*(struct obj **)((char *)DAT_060eea9c + 0x168), 1, 1.0);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006b2d20
void ObjectMysticRuinTree(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = TreeDisplayer;
			var1->mode = 1;
		}
		TreeDisplayer(tp);
	}
}
