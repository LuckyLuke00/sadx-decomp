#include "decls.h"
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

// STUB: SADX 0x008c86b0
void DisplayChaosCrashSphere(struct taskwk *twp, struct chaoswk *chwp, float param)
{
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
	*(long *)((char *)local_10 + 0x18) = AdjustAngle(*(long *)((char *)local_10 + 0x18), local_8g, 0x38e);
	local_10->pos = *pos;
	*(struct NJS_POINT3 *)((char *)local_ci + 0x4c) = *scale;
}
