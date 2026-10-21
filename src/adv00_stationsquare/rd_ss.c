#include "decls.h"

// FUNCTION: SADX 0x0067f8b0
void DestroyMapSS(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapSS);
	late_ReleaseTexture(&texlist_mapSS);
}
