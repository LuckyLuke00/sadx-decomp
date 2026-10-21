#include "decls.h"
void ChaosSurfacePatternChange(struct chaoswk *chwp);
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void njPushMatrix(float *);
void njTranslateV(float *, struct NJS_POINT3 *);
void effectWaterMove(struct taskwk *twp, struct chaoswk *cwp, struct obj *obj);
void njScaleV(float *, struct NJS_POINT3 *);
void CHAOS_SetMeshMode(int sw);
void CHAOS_DrawObject(struct obj *o);
void njPopMatrix(int);
extern struct obj object_c0_manju_c0_manju[1];

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

// STUB: SADX 0x008c8990
void SetParamDispChaosWater(struct NJS_POINT3 *pos, struct NJS_POINT3 *scale)
{
}
