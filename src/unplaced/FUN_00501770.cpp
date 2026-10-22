#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00501770
void FUN_00501770(struct taskwk *param_1)
{
	struct taskwk *local_8 = *(struct taskwk **)((char *)param_1 + 0x20);
	if (DAT_05b9d838 != 0)
		return;
	if (0 == SetObjectTexture())
	{
		___njSetTexture((struct NJS_TEXLIST *)*(int **)((char *)local_8 + 0x10));
	}
	occ_DrawObject(local_8, (struct obj *)*(int **)((char *)local_8 + 8), 1.0f);
}
