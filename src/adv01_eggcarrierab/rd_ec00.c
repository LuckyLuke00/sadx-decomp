#include "decls.h"

// FUNCTION: SADX 0x006930f0
void DestroyMapEC(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapEC);
	late_ReleaseTexture(&texlist_mapEC);
}
