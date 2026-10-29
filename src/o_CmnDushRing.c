#include "decls.h"
long CalcDashPosition(struct task *tp);
void DrawCmnDushRing(struct task *tp);
void FUN_005b5aa0(...);
float GetTargetDist(struct task *tp);
long CreateChkDashPlayer(struct task *tp, long pl_num, float dist);
extern int DAT_05b9d838;
extern struct obj DAT_05a83f08;
extern float DAT_05b3ec0c;
void FUN_005a8ae0(float *param_1, float *param_2, float *param_3);
void GetAngleXYV(const struct NJS_POINT3 *vec, long *ang_x, long *ang_y);

// STUB: SADX 0x008bb230
void ObjectCmnDushRing(struct task *tp)
{
}

// FUNCTION: SADX 0x008bb3b0
long InitCmnDushRing(struct task *tp)
{
	struct taskwk *local_cg;
	float local_8g;
	local_cg = tp->twp;
	local_cg->mode = 1;
	local_cg->counter.ptr = &DAT_05a83f08;
	tp->disp = DrawCmnDushRing;
	tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
	local_8g = GetTargetDist(tp);
	if (CreateChkDashPlayer(tp, 0, local_8g) == 0)
	{
		return 0;
	}
	if (CreateChkDashPlayer(tp, 1, local_8g) == 0)
	{
		return 0;
	}
	return 1;
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

// FUNCTION: SADX 0x008bb500
long CreateChkDashPlayer(struct task *tp, long pl_num, float dist)
{
	struct taskwk *local_10;
	struct taskwk *local_8g;
	struct task *local_cj;
	local_10 = tp->twp;
	local_cj = CreateChildTask(2, ChkDashPlayer, tp);
	if (local_cj == 0) {
		return 0;
	}
	local_8g = local_cj->twp;
	local_8g->pos = local_10->pos;
	local_8g->value.l = pl_num;
	local_8g->scl.x = dist;
	return 1;
}

// STUB: SADX 0x008bb570
void ChkDashPlayer(struct task *tp)
{
}

// STUB: SADX 0x008bb700
long CalcDashPosition(struct task *tp)
{
	return (long)0;
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
		njRotateX(0, (Uint16)local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, (Uint16)local_8->ang.y);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	ds_DrawObjectClip(&DAT_05a83f08, 1.0f);
	njPopMatrix(1);
}
