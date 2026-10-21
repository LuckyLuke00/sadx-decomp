#include "decls.h"
extern struct NJS_TEXLIST texlist_mapMR;
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2);

// FUNCTION: SADX 0x006a84a0
long LoadMapMR(unsigned short act)
{
	switch (act)
	{
	case 2:
		texLoadTexturePvmFile("map_mr_j", &texlist_mapMR);
		break;
	case 1:
		texLoadTexturePvmFile("map_mr_a", &texlist_mapMR);
		break;
	case 0:
		texLoadTexturePvmFile("map_mr_s", &texlist_mapMR);
		break;
	default:
		return 0;
	}
	FUN_004b6460(&texlist_mapMR, "mapMR");
	return 1;
}

// FUNCTION: SADX 0x006a8660
void DestroyMapMR(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapMR);
	late_ReleaseTexture(&texlist_mapMR);
}
