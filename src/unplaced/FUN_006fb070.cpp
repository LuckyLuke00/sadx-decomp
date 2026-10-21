#include "decls.h"

// FUNCTION: SADX 0x006fb070
void FUN_006fb070(struct task *param_1)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Chaos07 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Chaos07 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Chaos07 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Chaos07 + local_8))[DAT_05b3e0d0];
}
