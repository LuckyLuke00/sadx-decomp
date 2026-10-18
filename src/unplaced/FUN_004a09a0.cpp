#include "decls.h"

extern NJS_ARGB DAT_05b3df28;
extern NJS_ARGB DAT_05b39de4;

void njSetConstantMaterial(NJS_ARGB *param_1);
void FUN_004a0940(struct NJS_MODEL *model);
void FUN_004a0960(struct obj *object, struct NJS_MOTION *motion, float frame);

// FUNCTION: SADX 0x004a09a0
int FUN_004a09a0(struct NJS_MODEL *model)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0940(model);
	njSetConstantMaterial(&DAT_05b39de4);
	return 0;
}

// FUNCTION: SADX 0x004a09d0
void FUN_004a09d0(struct obj *object, struct NJS_MOTION *motion, float frame)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0960(object, motion, frame);
	njSetConstantMaterial(&DAT_05b39de4);
}
