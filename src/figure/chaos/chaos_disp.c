#include "decls.h"
extern struct obj object_c0_chibiman[];
extern signed char DAT_060dfd68;
extern float DAT_060dfd70[48];
extern float DAT_060dfe38[16];
extern short DAT_060dfc80;
extern "C" double atan2(double v, double u);
extern struct task *DAT_060dfe30;
extern void CHAOS_SetMeshMode(int sw);
extern void CHAOS_DrawObject(struct obj *o);
void ChaosSurfacePatternChange(struct chaoswk *chwp);
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void effectWaterMove(struct taskwk *twp, struct chaoswk *cwp, struct obj *obj);
void CHAOS_SetMeshMode(int sw);
void CHAOS_DrawObject(struct obj *o);
extern struct obj object_c0_manju_c0_manju[1];

// STUB: SADX 0x008c83f0
void InitDisplayChaosCrashSphere(struct taskwk *twp, struct chaoswk *chwp, int num)
{
}

// STUB: SADX 0x008c8580
void DisplayChaosCrashSphere0(struct taskwk *twp, struct chaoswk *chwp)
{
}

// FUNCTION: SADX 0x008c86b0
void DisplayChaosCrashSphere(struct taskwk *twp, struct chaoswk *chwp, float param)
{
	int local_8;

	for (local_8 = 0; local_8 < DAT_060dfd68; local_8++)
	{
		float local_c;
		float local_10l;
		float local_14;

		local_c = chwp->sp_scale.x * DAT_060dfe38[local_8];
		local_10l = chwp->sp_scale.y * DAT_060dfe38[local_8];
		local_14 = param * chwp->sp_scale.x * 0.5f;
		njPushMatrix(0);
		FUN_0067d830(0, ((struct NJS_POINT3 *)DAT_060dfd70)[local_8].x * local_14, ((struct NJS_POINT3 *)DAT_060dfd70)[local_8].y, ((struct NJS_POINT3 *)DAT_060dfd70)[local_8].z * local_14);
		FUN_0067d2d0(0, local_c, local_10l, local_c);
		CHAOS_SetMeshMode(2);
		CHAOS_DrawObject((struct obj *)&object_c0_chibiman);
		CHAOS_SetMeshMode(0);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x008c87c0
struct task *SetTaskDispChaosWater(long ang)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x008c8880
void DispChaosWater(struct task *tp)
{
	struct taskwk *local_cg;
	struct chaoswk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct chaoswk *)tp->awp;
	ChaosSurfacePatternChange(local_8g);
	___njSetTexture(local_8g->texlist);
	njPushMatrix(0);
	njTranslateV(0, &local_cg->pos);
	effectWaterMove(local_cg, local_8g, &object_c0_manju_c0_manju[0]);
	njScaleV(0, &local_8g->sp_scale);
	CHAOS_SetMeshMode(2);
	CHAOS_DrawObject(&object_c0_manju_c0_manju[0]);
	CHAOS_SetMeshMode(0);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008c8930
void DestDispChaosWater(struct task *tp)
{
	struct taskwk *local_cg;
	struct chaoswk *local_8g;
	local_cg = tp->twp;
	local_8g = (struct chaoswk *)tp->awp;
	*(unsigned long *)((char *)local_8g->texlist->textures + DAT_060dfc80 * 0xc + 8) = local_8g->old_texaddr;
	local_8g->sp_mode = 3;
	effectWaterMove(local_cg, local_8g, &object_c0_manju_c0_manju[0]);
}

// FUNCTION: SADX 0x008c8990
void SetParamDispChaosWater(struct NJS_POINT3 *pos, struct NJS_POINT3 *scale)
{
	struct taskwk *local_10;
	struct anywk *local_ci;
	long local_8g;
	local_10 = DAT_060dfe30->twp;
	local_ci = DAT_060dfe30->awp;
	local_8g = (long)(atan2(pos->z - local_10->pos.z, pos->x - local_10->pos.x) * 65536.0 / 6.283184);
	local_10->ang.y = AdjustAngle(local_10->ang.y, local_8g, 0x38e);
	local_10->pos = *pos;
	*(struct NJS_POINT3 *)((char *)local_ci + 0x4c) = *scale;
}
