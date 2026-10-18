#include "decls.h"

extern int DAT_05b92e24;
extern struct NJS_POINT3 DAT_05b42a98[32];
extern struct NJS_TEXLIST DAT_05b42c40[32];

// FUNCTION: SADX 0x004c1b70
void FUN_004c1b70(char *param_1)
{
	if (param_1 == 0)
	{
		DAT_05b92e24 = 0;
	}
	else
	{
		if (DAT_05b92e24 >= 32)
		{
			___OutputDebugString("MSGC_Close:?????????????\n");
		}
		DAT_05b42a98[DAT_05b92e24] = *(struct NJS_POINT3 *)(param_1 + 0x38);
		DAT_05b42c40[DAT_05b92e24] = *(struct NJS_TEXLIST *)(param_1 + 0x30);
		DAT_05b42c40[DAT_05b92e24].textures = (struct NJS_TEXNAME *)&DAT_05b42a98[DAT_05b92e24];
		DAT_05b92e24++;
	}
}
