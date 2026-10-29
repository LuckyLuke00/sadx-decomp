#include "decls.h"

extern NJS_ARGB DAT_05b3df28;
extern NJS_ARGB DAT_05b39de4;

void FUN_004a0940(struct NJS_MODEL *param_1);
void FUN_004a0960(struct obj *param_1, struct NJS_MOTION *param_2, float param_3);

// FUNCTION: SADX 0x004a09a0
int FUN_004a09a0(struct NJS_MODEL *param_1)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0940(param_1);
	njSetConstantMaterial(&DAT_05b39de4);
	return 0;
}

// FUNCTION: SADX 0x004a09d0
void FUN_004a09d0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0960(param_1, param_2, param_3);
	njSetConstantMaterial(&DAT_05b39de4);
}
