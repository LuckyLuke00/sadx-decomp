#include "decls.h"
extern void *DAT_0387c630;
extern void *DAT_0387c634;
extern void *DAT_0387c638;
extern void *DAT_0387c63c;

// FUNCTION: SADX 0x007f2dd0
void FUN_007f2dd0(void)
{
	DAT_05b3e040 = *(struct NJS_ARGB *)((char *)DAT_0387c63c + DAT_05b3e0d0 * 0x10);
	DAT_05b3e080 = *(struct NJS_POINT2 *)((char *)DAT_0387c634 + DAT_05b3e0d0 * 8);
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = *(struct NJS_POINT2 *)((char *)DAT_0387c638 + DAT_05b3e0d0 * 8);
	DAT_05b3e074 = *(struct NJS_POINT3 *)((char *)DAT_0387c630 + DAT_05b3e0d0 * 0xc);
}
