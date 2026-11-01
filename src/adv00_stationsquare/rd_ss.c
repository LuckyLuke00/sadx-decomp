#include "decls.h"
int checkInSsHodel();

// STUB: SADX 0x0067f3f0
int checkInSsHodel()
{
	return (int)0;
}

// FUNCTION: SADX 0x0067f640
void ss_bgmcontrol(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	var1->wtimer--;
	if ((short)var1->wtimer < 0)
	{
		if (dsCheckBGMActive())
		{
			RoundBGM_Play(var1->mode);
		}
		if ((char)DAT_05b9d744 == 5)
		{
			Serif_Play(0x627);
		}
		DestroyTask(tp);
	}
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
