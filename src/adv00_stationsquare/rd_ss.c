#include "decls.h"
int checkInSsHodel();

// STUB: SADX 0x0067f3f0
int checkInSsHodel()
{
	return (int)0;
}

// STUB: SADX 0x0067f640
void ss_bgmcontrol(struct task *tp)
{
}

// FUNCTION: SADX 0x0067f690
long LoadMapSS(unsigned short act)
{
	if (act > 5)
	{
		return 0;
	}
	texLoadTexturePvmFile("map_ss", &texlist_mapSS);
	FUN_004b6460(&texlist_mapSS, "map_ss");
	return 1;
}

// FUNCTION: SADX 0x0067f8b0
void DestroyMapSS(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapSS);
	late_ReleaseTexture(&texlist_mapSS);
}
