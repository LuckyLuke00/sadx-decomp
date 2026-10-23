#include "decls.h"
extern int DAT_05b9d838;
extern struct obj DAT_05a83f08;
extern float DAT_05b3ec0c;
void FUN_005a8ae0(float *param_1, float *param_2, float *param_3);
void GetAngleXYV(const struct NJS_POINT3 *vec, long *ang_x, long *ang_y);
double njScalor(struct NJS_POINT3 *param_1);

// STUB: SADX 0x008bb3b0
long InitCmnDushRing(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x008bb440
float GetTargetDist(struct task *tp)
{
	struct taskwk *local_cg;
	float local_8g;
	local_cg = tp->twp;
	if (local_cg->scl.x == 0.0f && local_cg->scl.y == 0.0f && local_cg->scl.z == 0.0f)
	{
		return 400.0f;
	}
	else
	{
		FUN_005a8ae0(&local_cg->scl.x, &local_cg->pos.x, &DAT_05b3ec0c);
		GetAngleXYV((const struct NJS_POINT3 *)&DAT_05b3ec0c, &local_cg->ang.x, &local_cg->ang.y);
		local_8g = (float)njScalor((struct NJS_POINT3 *)&DAT_05b3ec0c);
		if (local_8g > 1500.0f)
		{
			local_8g = 1500.0f;
		}
		return local_8g;
	}
}

// FUNCTION: SADX 0x008bb8e0
void DrawCmnDushRing(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
		return;
	if (dsCheckViewV(&local_8->pos, 100.0f) == 0)
		return;
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.x != 0)
		njRotateX(0, local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, local_8->ang.y);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	ds_DrawObjectClip(&DAT_05a83f08, 1.0f);
	njPopMatrix(1);
}
