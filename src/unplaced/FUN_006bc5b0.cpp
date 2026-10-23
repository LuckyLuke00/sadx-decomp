#include "decls.h"

// FUNCTION: SADX 0x006bc5b0
void FUN_006bc5b0(struct task *param_1)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Adv03 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Adv03 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 3000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Adv03 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Adv03 + local_8))[DAT_05b3e0d0];
}
