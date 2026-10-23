#include "decls.h"

// FUNCTION: SADX 0x006c55e0
void Bg_Bossegm2(struct task *tp)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Egm02 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Egm02 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Egm02 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Egm02 + local_8))[DAT_05b3e0d0];
}

// STUB: SADX 0x006c56d0
void Rd_Bossegm2(struct task *tp)
{
}
