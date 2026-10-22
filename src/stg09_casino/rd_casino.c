#include "decls.h"
extern int DAT_060dbcb0;
extern unsigned char DAT_048093d9;
extern short *DAT_05baf368;
extern int DAT_05cd14d4;
extern int DAT_060dbc34;
extern char DAT_048093d8;

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

// STUB: SADX 0x0086a190
void SetPlayerPinball(struct task *tp)
{
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
