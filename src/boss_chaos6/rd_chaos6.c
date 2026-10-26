#include "decls.h"
extern struct NJS_ARGB *pFogTable_Chaos06[];
extern struct NJS_POINT2 *pClipSky_Chaos06[];
extern struct NJS_POINT2 *pClipMap_Chaos06[];
extern struct NJS_POINT3 *pScale_Chaos06[];

// FUNCTION: SADX 0x006f4b60
void RdChaos6Init(struct task *tp)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Chaos06 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Chaos06 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Chaos06 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Chaos06 + local_8))[DAT_05b3e0d0];
}

// STUB: SADX 0x006f4c10
void chaos6_gdcontrol(struct task *tp)
{
}

// STUB: SADX 0x006f4c50
void Rd_Chaos6(struct task *tp)
{
}
