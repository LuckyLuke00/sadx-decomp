#include "decls.h"
extern struct ___stcFog *DAT_0286d3a0[];
extern struct ___stcClip *DAT_0286d398[];
extern struct ___stcClip *DAT_0286d39c[];
extern struct NJS_POINT3 *DAT_0286d394[];

// FUNCTION: SADX 0x006e2710
void FUN_006e2710(struct task *param_1)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)DAT_0286d3a0 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)DAT_0286d398 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)DAT_0286d39c + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)DAT_0286d394 + local_8))[DAT_05b3e0d0];
}
