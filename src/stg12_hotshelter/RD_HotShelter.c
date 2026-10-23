#include "decls.h"
void FUN_008a2300();
extern struct NJS_ARGB DAT_05b3e040;
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT3 DAT_05b3e074;
extern struct NJS_POINT2 DAT_05b3e080;
extern int DAT_05b3e0d0;
extern short DAT_05b9d744;
extern struct NJS_ARGB *pFogTable_Stg12[];
extern struct NJS_POINT2 *pClipSky_Stg12[];
extern struct NJS_POINT2 *pClipMap_Stg12[];
extern struct NJS_POINT3 *pScale_Stg12[];
extern int DAT_060dd394;
extern int DAT_060dd388;
extern int DAT_060dd38c;

// FUNCTION: SADX 0x008a2240
void ACT1_init(struct task *tp)
{
	ADXTaskInit();
	RoundBGM_Play(0x4f);
	InitAquariumSequence();
	InitialDynamite();
	ClearAllSwitches();
	if (GetPlayerNumber() == 7)
	{
		if (DAT_060dd388 != 0)
		{
			FUN_0058b860(0, 1);
		}
		if (DAT_060dd38c != 0)
		{
			DAT_060dd394 |= 1;
		}
	}
}

// FUNCTION: SADX 0x008a2290
void FUN_008a2290()
{
	ADXTaskInit();
	RoundBGM_Play(0x50);
	InitialDynamite();
	InitBoxSwitch();
	ClearAllSwitches();
}

// FUNCTION: SADX 0x008a22b0
void FUN_008a22b0()
{
	ADXTaskInit();
	RoundBGM_Play(0x50);
	InitialDynamite();
	ClearAllSwitches();
	InitTunnelManager();
}

// FUNCTION: SADX 0x008a22d0
void FUN_008a22d0()
{
	ADXTaskInit();
	RoundBGM_Play(0x50);
	InitialDynamite();
	ClearAllSwitches();
}

// FUNCTION: SADX 0x008a22f0
void InitInitShelter()
{
	DAT_060dd388 = 0;
	DAT_060dd38c = 0;
}

// FUNCTION: SADX 0x008a2300
void FUN_008a2300()
{
	SetViewAngle(0x31c7);
	___njSetBackColor(0, 0, 0);
}

// STUB: SADX 0x008a23d0
void Bg_HotShelter(struct task *tp)
{
}
