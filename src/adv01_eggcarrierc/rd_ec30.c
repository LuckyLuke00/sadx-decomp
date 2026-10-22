#include "decls.h"

// STUB: SADX 0x0069db40
void FUN_0069db40(void)
{
}

// STUB: SADX 0x0069dbe0
void FUN_0069dbe0(struct task *tp)
{
}

// FUNCTION: SADX 0x0069dc30
long LoadMapECH(unsigned short act)
{
	if (act > 5)
		return 0;
	texLoadTexturePvmFile("map_ec_h", &texlist_mapECH);
	FUN_004b6460(&texlist_mapECH, "map_ec_h");
	return 1;
}

// FUNCTION: SADX 0x0069ddd0
void DestroyMapECH(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapECH);
	late_ReleaseTexture(&texlist_mapECH);
}
