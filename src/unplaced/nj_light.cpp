#include "decls.h"

// FUNCTION: SADX 0x0067e500
void njTranslateLightV(struct NJS_LIGHT *param_1, struct NJS_POINT3 *param_2)
{
	njTranslateV((float *)param_1, param_2);
}

// FUNCTION: SADX 0x0067e510
void FUN_0067e510(float *param_1, float param_2, float param_3, float param_4)
{
	FUN_0067d830(param_1, param_2, param_3, param_4);
}

// FUNCTION: SADX 0x0067e540
void njUnitLightMatrix(struct NJS_LIGHT *param_1)
{
	njUnitMatrix((float *)param_1);
}
