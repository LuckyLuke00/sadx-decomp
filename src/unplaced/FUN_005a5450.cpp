#include "decls.h"

// FUNCTION: SADX 0x005a5450
void FUN_005a5450(struct NJS_TEXLIST *param_1)
{
	struct NJS_TEXLIST *local_8g;
	int local_cg;
	local_8g = *(struct NJS_TEXLIST **)((char *)param_1 + 0x24);
	local_cg = *(int *)((char *)local_8g + 4);
	if (local_cg != 0)
	{
		late_ReleaseTexture((struct NJS_TEXLIST *)local_cg);
		*(int *)((char *)local_8g + 4) = 0;
	}
}
