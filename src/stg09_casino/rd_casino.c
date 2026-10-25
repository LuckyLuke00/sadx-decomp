#include "decls.h"
extern struct NJS_TEXLIST texlist_balls;
extern struct NJS_TEXLIST texlist_obj_casino;
extern struct NJS_TEXLIST texlist_obj_casino2;
extern struct NJS_TEXLIST texlist_obj_casino8;
extern struct NJS_TEXLIST texlist_obj_casino9;
extern struct NJS_ARGB DAT_05b3e040;
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT3 DAT_05b3e074;
extern struct NJS_POINT2 DAT_05b3e080;
extern int DAT_05b3e0d0;
extern struct NJS_ARGB *pFogTable_Stg09[];
extern struct NJS_POINT2 *pClipSky_Stg09[];
extern struct NJS_POINT2 *pClipMap_Stg09[];
extern struct NJS_POINT3 *pScale_Stg09[];
extern short DAT_05b9d744;
extern int DAT_060dbcb0;
extern unsigned char DAT_048093d9;
extern short *DAT_05baf368;
extern int DAT_05cd14d4;
extern int DAT_060dbc34;
extern char DAT_048093d8;

// FUNCTION: SADX 0x00869bc0
void LoadTextureOnCasino(long No)
{
	unsigned int local_8 = (unsigned char)DAT_05b9d744 * 4;
	DAT_05b3e040 = (*(struct NJS_ARGB **)((char *)pFogTable_Stg09 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080 = (*(struct NJS_POINT2 **)((char *)pClipSky_Stg09 + local_8))[DAT_05b3e0d0];
	DAT_05b3e080.y -= 1000.0;
	DAT_05b3e050 = (*(struct NJS_POINT2 **)((char *)pClipMap_Stg09 + local_8))[DAT_05b3e0d0];
	DAT_05b3e074 = (*(struct NJS_POINT3 **)((char *)pScale_Stg09 + local_8))[DAT_05b3e0d0];
}

// FUNCTION: SADX 0x00869c70
void CasinoBgmControl(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (EV_CheckCansel() == 0)
	{
		var1->btimer--;
		if (var1->btimer == 0)
		{
			ADXTaskInit();
			BGM_Play(var1->mode);
			DestroyTask(tp);
		}
	}
}

// FUNCTION: SADX 0x00869cb0
void ReleaseTextureOnCasino(long No)
{
	if (No == 0)
	{
		if ((DAT_060dbcb0 & 0x40000000) != 0)
		{
			DAT_060dbcb0 &= 0xbfffffff;
			late_ReleaseTexture(&texlist_obj_casino9);
		}
		if ((DAT_060dbcb0 & 0x80000000) != 0)
		{
			DAT_060dbcb0 &= 0x7fffffff;
			late_ReleaseTexture(&texlist_obj_casino8);
		}
	}
	else
	{
		if ((DAT_060dbcb0 & 0x10000000) != 0)
		{
			DAT_060dbcb0 &= 0xefffffff;
			late_ReleaseTexture(&texlist_obj_casino);
			late_ReleaseTexture(&texlist_balls);
		}
		if ((DAT_060dbcb0 & 0x20000000) != 0)
		{
			DAT_060dbcb0 &= 0xdfffffff;
			late_ReleaseTexture(&texlist_obj_casino2);
			late_ReleaseTexture(&texlist_balls);
		}
	}
}

// FUNCTION: SADX 0x00869e30
void RdCasinoCheckAct1toAct3(struct task *tp)
{
	if (ChkGameMode() == 0)
	{
		return;
	}
	if (GetPlayerCharacterName(0) == 3)
	{
		return;
	}
	if (DAT_060dbc34 != 4)
	{
		return;
	}
	ADX_Close();
	if (DAT_060dbcb0 & 0x40000000)
	{
		DAT_060dbcb0 &= 0xbfffffff;
		late_ReleaseTexture(&texlist_obj_casino9);
	}
	if (DAT_060dbcb0 & 0x80000000)
	{
		DAT_060dbcb0 &= 0x7fffffff;
		late_ReleaseTexture(&texlist_obj_casino8);
	}
	DAT_05cd14d4 = 1;
	LandChangeStage(3);
	AddSetStage(3);
	AddCameraStage(3);
	AdvanceAct(3);
	SetPlayerInitialPosition((struct taskwk *)DAT_05baf368);
	*(unsigned char *)tp->twp = 0;
	DAT_060dbc34 = 0;
	DAT_048093d9 = 3;
}

// FUNCTION: SADX 0x00869f00
void RdCasinoCheckAct1toAct4(struct task *tp)
{
	if (ChkGameMode() != 0 && GetPlayerCharacterName(0) != 3 && DAT_060dbc34 == 1)
	{
		ADX_Close();
		ReleaseTextureOnCasino(1);
		LandChangeStage(-1);
		AddSetStage(-1);
		AddCameraStage(-1);
		AdvanceAct(-1);
		SetPlayerInitialPosition((*(struct taskwk *(*))&DAT_05baf368));
		tp->twp->mode = 0;
		DAT_060dbc34 = 0;
		DAT_048093d8 = 0;
	}
}

// FUNCTION: SADX 0x0086a0d0
void CasinoExit(struct task *tp)
{
	ADX_Close();
	SetViewAngle(0x31c7);
	SetUserGravityXZ(0, 0);
	if (DAT_060dbcb0 & 0x40000000)
	{
		DAT_060dbcb0 &= 0xbfffffff;
		late_ReleaseTexture(&texlist_obj_casino9);
	}
	if (DAT_060dbcb0 & 0x80000000)
	{
		DAT_060dbcb0 &= 0x7fffffff;
		late_ReleaseTexture(&texlist_obj_casino8);
	}
	if (DAT_060dbcb0 & 0x10000000)
	{
		DAT_060dbcb0 &= 0xefffffff;
		late_ReleaseTexture(&texlist_obj_casino);
		late_ReleaseTexture(&texlist_balls);
	}
	if (DAT_060dbcb0 & 0x20000000)
	{
		DAT_060dbcb0 &= 0xdfffffff;
		late_ReleaseTexture(&texlist_obj_casino2);
		late_ReleaseTexture(&texlist_balls);
	}
	___njFogDisable();
}

// FUNCTION: SADX 0x0086a190
void SetPlayerPinball(struct task *tp)
{
	short var1;
	var1 = (short)DAT_05b9d744 & 0xff;
	if (var1 == 0 || var1 == 1)
	{
		FreeTask(tp);
		return;
	}
	{
		unsigned char var2;
		var2 = tp->twp->btimer;
		tp->twp->btimer = var2 - 1;
		if (var2 != 0)
			return;
		SetInputP(0, 0x2d);
		FreeTask(tp);
	}
}

// FUNCTION: SADX 0x0086a3b0
void SetObjectTexture2(long No)
{
	if (No == 0xc)
	{
		___njSetTexture(&texlist_obj_casino9);
		return;
	}
	if (No == 0x22)
	{
		___njSetTexture(&texlist_obj_casino);
		return;
	}
	for (;;)
	{
	}
}
