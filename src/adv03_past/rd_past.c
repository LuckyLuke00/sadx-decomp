#include "decls.h"

// FUNCTION: SADX 0x006bc840
void DestroyMapPAST(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapPAST);
	late_ReleaseTexture(&texlist_mapPAST);
}
