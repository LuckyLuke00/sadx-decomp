#include "decls.h"

// FUNCTION: SADX 0x0069ddd0
void DestroyMapECH(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapECH);
	late_ReleaseTexture(&texlist_mapECH);
}
