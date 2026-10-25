#include "decls.h"

// FUNCTION: SADX 0x00472980
void FUN_00472980(struct NJS_SPRITE *param_1, int param_2, float param_3, unsigned long param_4)
{
	if (param_3 >= -3.0f && param_3 < 12048.0f)
	{
		param_3 = (float)((double)param_3 + 22048.0);
	}
	late_DrawSprite2D(param_1, param_2, param_3, param_4, 4);
}
