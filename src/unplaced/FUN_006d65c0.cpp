#include "decls.h"
extern struct ___stcFog *pFogTable_Robo[1];
extern struct ___stcClip *pClipSky_Robo[1];
extern struct ___stcClip *pClipMap_Robo[1];
extern struct NJS_POINT3 *pScale_Robo[1];

// FUNCTION: SADX 0x006d65c0
void FUN_006d65c0()
{
	DAT_05b3e040 = *(struct NJS_ARGB *)((char *)pFogTable_Robo[0] + DAT_05b3e0d0 * 0x10);
	DAT_05b3e080 = *(struct NJS_POINT2 *)((char *)pClipSky_Robo[0] + DAT_05b3e0d0 * 8);
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = *(struct NJS_POINT2 *)((char *)pClipMap_Robo[0] + DAT_05b3e0d0 * 8);
	DAT_05b3e074 = *(struct NJS_POINT3 *)((char *)pScale_Robo[0] + DAT_05b3e0d0 * 0xc);
}
