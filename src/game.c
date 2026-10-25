#include <stdlib.h>
#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
void GenocideTask();
extern int DAT_05cd0f24;
extern int DAT_05cda170;
extern int DAT_05cda168;
extern int DAT_05cda16c;
extern int DAT_05cda160;
extern int DAT_05cda164;
extern unsigned char DAT_05b3ea26;
extern unsigned char DAT_05b9d776;
extern unsigned char DAT_05cccc6a[];
extern unsigned char DAT_05b3ea14;
extern void FUN_005a4d70();
extern int DAT_05cda154;
extern short DAT_05b93710;
extern int DAT_05b9d778;
extern char DAT_05cccc69;
extern void SetDefaultGravity();
extern void ResetNumPlayer();
extern short GetNumPlayer();
extern void pdVibMxStop(int param_1);
extern void njSetMaterialCallBackFunc(void (*)(void));
extern void ChangePowerMaterial();
extern long GM_CheckMode();
extern struct GM_EVENT_TABLE cleareventtable[1];
extern int DAT_05b9d728;
void GM_WaitEventE(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void ADX_Close();
void EV_Load2(int no);
void EV_Exec2();
int EV_CheckExec(int no);
void ReleaseMissionObject();
void FUN_007d21b0(void *param_1);
extern unsigned char DAT_05b3739a;
void FUN_004c8770();
extern short DAT_05b9d720;
extern short DAT_05b9d748;
extern short DAT_05b9d770;
extern short DAT_05b9d72c;
extern short DAT_05b9d730;
void FUN_004c9380();
extern unsigned short DAT_05b9d718;
void FUN_004f3f00();
void pdVibMxStop(int param_1);
extern int DAT_05b9d838;
extern int DAT_05b9d83c;
extern short DAT_05b9d740;
void FUN_00554a70();
extern short DAT_05b9d774;
extern int DAT_05b3e05c;
extern short DAT_05b9d73c;
void FUN_004c76e0();

extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern char DAT_05b42c1c;
extern unsigned char DAT_05b3ea25;

int FUN_005030d0();

// FUNCTION: SADX 0x004c4fa0
void PauseEnable()
{
	ssPauseEnable = 1;
}

// FUNCTION: SADX 0x004c4fb0
void PauseDisable()
{
	ssPauseEnable = 0;
}

// FUNCTION: SADX 0x004c4fc0
void StartTheFirstGame()
{
	int local_8;

	InitGCMemocaState();
	SetPlayerNumberForGame(0);
	InitTime();
	InitScore();
	SeqInit();
	DAT_05b42c1c = 0;
	InitGame();
	local_8 = FUN_005030d0();
	DAT_05b3ea25 = 0;
	srand(0xdead0cab);
}

// FUNCTION: SADX 0x004c5120
void GM_WaitEventS(struct task *tp)
{
	ADX_Close();
	EV_Load2(((struct taskwk *)tp->twp)->wtimer);
	EV_Exec2();
	tp->exec = GM_WaitEvent;
}

// FUNCTION: SADX 0x004c5150
void GM_WaitEvent(struct task *tp)
{
	if (EV_CheckCansel() == 0)
	{
		DestroyTask(tp);
		PadReadOn();
		if ((short)DAT_05b9d724 != 0x13)
		{
			PauseEnable();
		}
		WakeTimer();
	}
}

// FUNCTION: SADX 0x004c5190
long GM_CheckClearEvent()
{
	struct GM_EVENT_TABLE *local_8;

	local_8 = cleareventtable;
	if (DAT_05b3e05c == 9)
	{
		return 0;
	}
	while (local_8->stage != 0x2b)
	{
		if (local_8->stage == DAT_05b9d724 && local_8->act == DAT_05b9d744 && local_8->chara == DAT_05b9d718)
		{
			if (EV_CheckExec(local_8->evexe) != 0)
			{
				local_8 = local_8 + 1;
				continue;
			}
			ADX_Close();
			EV_Load2(local_8->evexe);
			EV_Exec2();
			CreateElementalTask(0, 0, GM_WaitEventE);
			DAT_05b9d728 = 0xffffffff;
			return 1;
		}
		local_8 = local_8 + 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004c5260
void GM_WaitEventE(struct task *tp)
{
	tp->exec = GM_WaitEvent;
	tp->dest = GM_WaitEventEDestruct;
}

// FUNCTION: SADX 0x004c5280
void GM_WaitEventEDestruct(struct task *tp)
{
	SetChangeGameMode(1);
}

// FUNCTION: SADX 0x004c5290
long GM_CheckMode()
{
	long local_8;

	if ((short)DAT_05b9d724 <= 0xe)
	{
		local_8 = 2;
	}
	else if ((short)DAT_05b9d724 <= 0x19)
	{
		local_8 = 2;
	}
	else if ((short)DAT_05b9d724 <= 0x22)
	{
		local_8 = 1;
	}
	else if ((short)DAT_05b9d724 <= 0x26)
	{
		local_8 = 2;
	}
	else
	{
		local_8 = 1;
	}
	return local_8;
}

// FUNCTION: SADX 0x004c5300
long InitGame()
{
	DAT_05b9d73c = 0x15;
	DAT_05b9d774 = 0;
	DAT_05cda154 = 0;
	SetDefaultGravity();
	DAT_05b93710 = 0;
	DAT_05b9d778 = 0;
	if (DAT_05cccc69 & 2)
	{
		DAT_05b42c1c = 0;
	}
	else
	{
		DAT_05b42c1c = 1;
	}
	if (GetNumPlayer() < 4)
	{
		ResetNumPlayer();
	}
	pdVibMxStop(0);
	njSetMaterialCallBackFunc(ChangePowerMaterial);
	return GM_CheckMode();
}

// FUNCTION: SADX 0x004c66b0
bool IsNeedForcePause()
{
	if (ucInputStatus != 0 && ucInputStatusForEachPlayer[0] != 0)
	{
		return false;
	}
	else
	{
		return false;
	}
}

// FUNCTION: SADX 0x004c66e0
void FUN_004c66e0()
{
	ActionEnd();
	FUN_004c76e0();
	SeqSetClearActionFlag(DAT_05b9d724);
	if (DAT_05b3e05c == 9)
	{
		SetNextTrialStage();
	}
	else
	{
		FUN_004c9c90();
	}
	DAT_05b9d73c = 0x11;
}

// FUNCTION: SADX 0x004c6720
void GoNextAction()
{
	short local_8;

	ADX_Close();
	if ((short)DAT_05b9d748 == DAT_05b9d724)
	{
		DAT_05b9d73c = 4;
		local_8 = (short)DAT_05b9d770 - DAT_05b9d744;
		LandChangeStage(local_8);
		AddSetStage(local_8);
		AddCameraStage(local_8);
		AdvanceActLocal(local_8);
		SetPlayerInitialPosition(DAT_05baf368[0]);
		SetInputP(0, 0x18);
		FUN_004c76e0();
		InitFadeIn();
		while (FadeIn())
		{}
	}
	else
	{
		ActionEnd();
		FUN_004c76e0();
		DAT_05b9d73c = 0x11;
	}
}

// STUB: SADX 0x004c75c0
void GoNextAdventure()
{
	short local_8;

	if (DAT_05b9d748 == DAT_05b9d724)
	{
		DAT_05b9d73c = 4;
		local_8 = DAT_05b9d770 - DAT_05b9d744;
		LandChangeStage(local_8);
		AddSetStage(local_8);
		AddCameraStage(local_8);
		DAT_05b9d730 = DAT_05b9d724;
		DAT_05b9d72c = DAT_05b9d744;
		AdvanceActLocal(local_8);
		SetPlayerInitialPosition(DAT_05baf368[0]);
		SetInputP(0, 0x18);
		FUN_004c76e0();
		InitFadeIn();
		while (FadeIn())
			;
	}
	else
	{
		FUN_004c87a0();
		FUN_004c76e0();
		DAT_05b9d73c = 0x11;
	}
}

// FUNCTION: SADX 0x004c76a0
void SetChangeGameMode(short mode)
{
	if (mode == 1 && GM_CheckClearEvent() != 0)
		return;
	DAT_05b9d774 = mode;
}

// FUNCTION: SADX 0x004c76d0
short FUN_004c76d0()
{
	return DAT_05b9d774;
}

// FUNCTION: SADX 0x004c76e0
void FUN_004c76e0()
{
	DAT_05b9d774 = 0;
}

// FUNCTION: SADX 0x004c7950
void FUN_004c7950()
{
	DAT_05b9d740 = 0;
	InitContinueData();
	SetDefaultGravity();
	if ((short)DAT_05b9d724 == 0x23)
	{
		FUN_00554a70();
	}
	if ((short)DAT_05b9d724 == 9)
	{
		if (GetPlayerCharacterName(0) == 0)
		{
			FUN_00554a70();
		}
	}
}

// FUNCTION: SADX 0x004c79a0
void FUN_004c79a0()
{
	GameInit();
}

// FUNCTION: SADX 0x004c80c0
void InitGameWorks()
{
	if (DAT_05cd0f24 == 1)
	{
		srand(0xdead0cab);
	}
	ssPauseEnable = 0;
	DAT_05b3ea26 = 0xff;
	if (DAT_05cda170 == 0)
	{
		DAT_05cda168 = 0;
	}
	else
	{
		DAT_05cda168 = 1;
		srand(0);
		if (DAT_05cda170 == 1)
		{
			DAT_05cda16c = 0;
		}
		else
		{
			DAT_05cda16c = 1;
		}
	}
	DAT_05cda160 = 0;
	DAT_05cda164 = 0xcbc0000;
	PadReadOnP(3);
	InitRing();
	FUN_00554a20();
	DAT_05b9d776 = 0;
}

// FUNCTION: SADX 0x004c8170
void FUN_004c8170()
{
	SeqInitStage();
	GameInit();
	ADXTaskInit();
}

// FUNCTION: SADX 0x004c8190
short FUN_004c8190(void)
{
	short local_cg;
	int local_8g;
	local_cg = 0;
	local_8g = DAT_05b9d83c;
	GameLoop_with_SyoriOchiTaisaku();
	DisplayScore();
	DisplayTimer();
	return local_cg;
}

// FUNCTION: SADX 0x004c8330
short GameLoop()
{
	short local_8;

	local_8 = 0;
	GetSwitchData();
	FUN_005a4d70();
	if (DAT_05b3e05c == 0xa)
	{
		MissionMain();
	}
	LoopTask();
	CCL_Analyze();
	SpLoop();
	CL_ColPolListUpRangeIn();
	if (EV_CheckCansel() == 0)
	{
		if (GM_CheckMode() != 1)
		{
			AdvanceTime();
		}
		DAT_05b3ea16 = 0;
	}
	else
	{
		DAT_05b3ea16 = 0xff;
	}
	if (DAT_05b3e05c == 9)
	{
		if ((short)DAT_05b9d724 <= 0x19)
		{
			if ((short)DAT_05b9d724 > 0xe)
			{
				DAT_05b3ebba = 0xff;
			}
		}
	}
	return local_8;
}

// FUNCTION: SADX 0x004c83c0
unsigned short FUN_004c83c0()
{
	unsigned short local_8;
	local_8 = 0;
	GameLoop_with_SyoriOchiTaisaku();
	DisplayScore();
	return local_8;
}

// STUB: SADX 0x004c83e0
short PauseLoop()
{
	return (short)0;
}

// FUNCTION: SADX 0x004c8570
unsigned short FUN_004c8570(void)
{
	unsigned short local_8;
	local_8 = 0;
	GetSwitchData();
	DAT_05b9d838 = 0;
	DisplayTask();
	DisplayScore();
	DisplayTimer();
	SpLoopOnlyDisplay();
	return local_8;
}

// FUNCTION: SADX 0x004c85b0
void FUN_004c85b0()
{
	InitMemory();
	InitTask();
}

// FUNCTION: SADX 0x004c85c0
void FUN_004c85c0()
{
	dsStop_all();
	GenocideTask();
}

// FUNCTION: SADX 0x004c85d0
short FUN_004c85d0()
{
	short local_8;
	local_8 = 0;
	GetSwitchData();
	DAT_05b9d838 = 0;
	LoopTask();
	return local_8;
}

// STUB: SADX 0x004c8600
void ActionEnd()
{
}

// FUNCTION: SADX 0x004c8770
void FUN_004c8770()
{
	dsStop_all();
	TH_DestroyAll();
	FUN_004f3f00();
	SpDestroyAll();
	pdVibMxStop(0);
}

// FUNCTION: SADX 0x004c87a0
void FUN_004c87a0()
{
	FUN_004c8770();
}

// STUB: SADX 0x004c87b0
void EndStage()
{
}

// FUNCTION: SADX 0x004c8880
void GM_SECall(long se)
{
	struct task *local_8;

	local_8 = CreateElementalTask(8, 1, GM_SEControle);
	if (local_8 != NULL)
	{
		*(int *)((char *)local_8->awp + 0) = 5;
		*(int *)((char *)local_8->awp + 4) = se;
		*(int *)((char *)local_8->awp + 8) = 1;
	}
}

// FUNCTION: SADX 0x004c88d0
void GM_SEControle(struct task *tp)
{
	struct anywk *local_8;

	local_8 = tp->awp;
	local_8->work.sl[0]--;
	if (local_8->work.sl[0] <= 0)
	{
		switch (local_8->work.sl[2])
		{
		case 0:
			BGM_Play(local_8->work.sl[1]);
			break;
		case 1:
			dsPlay_oneshot(local_8->work.sl[1], 0, 0, 0);
			break;
		}
		DestroyTask(tp);
	}
}

// FUNCTION: SADX 0x004c8950
void GM_BGM_Play(long bgm)
{
	struct task *local_8;

	local_8 = CreateElementalTask(8, 1, GM_SEControle);
	if (local_8 != 0)
	{
		local_8->awp->work.sl[0] = 5;
		local_8->awp->work.sl[1] = bgm;
		local_8->awp->work.sl[2] = 0;
	}
}

// STUB: SADX 0x004c8c90
void WaitLandPlayer(struct task *tp)
{
}

// FUNCTION: SADX 0x004c91e0
void SetPlayerNumberForGame(unsigned short pno)
{
	long local_8;

	ReleasePlayersTexture(DAT_05b9d718);
	local_8 = DAT_05b9d718;
	if (local_8 > 4)
	{
		local_8--;
	}
	if (local_8 > 1)
	{
		local_8--;
	}
	DAT_05b9d718 = pno;
	LoadPlayerMotionData(DAT_05b9d718);
	local_8 = DAT_05b9d718;
	if (local_8 > 4)
	{
		local_8--;
	}
	if (local_8 > 1)
	{
		local_8--;
	}
	DAT_05b3ea14 = DAT_05cccc6a[local_8];
	if (GetNumPlayer() < 4)
	{
		ResetNumPlayer();
	}
	ClearExtraDisplay();
}

// FUNCTION: SADX 0x004c9290
void SetPlayerNumber(unsigned short pno)
{
	DAT_05b9d718 = pno;
}

// FUNCTION: SADX 0x004c92a0
long GetPlayerNumber()
{
	return DAT_05b9d718;
}

// FUNCTION: SADX 0x004c92b0
long GetCountKilledPlayer()
{
	return DAT_05b9d740;
}

// FUNCTION: SADX 0x004c92c0
void SetNextStageNumberForReturn()
{
	struct GM_START_POSANG *local_8;

	DAT_05b9d748 = DAT_05b9d730;
	DAT_05b9d770 = DAT_05b9d72c;
	local_8 = paRPTable[DAT_05b9d718];
	DAT_05b9d778 = 0;
	while (local_8->stage != 0x2b)
	{
		if (local_8->stage == DAT_05b9d724)
		{
			DAT_05b9d778 = (int)local_8;
			if (DAT_05b9d724 == 3)
			{
				DAT_05b9d770 = 5;
			}
			break;
		}
		local_8 = (struct GM_START_POSANG *)((char *)local_8 + 0x14);
	}
}

// FUNCTION: SADX 0x004c9350
void SetStageNumber(unsigned char stg, unsigned char act)
{
	FUN_004c9380();
	DAT_05b9d724 = stg;
	DAT_05b9d744 = act;
}

// FUNCTION: SADX 0x004c9380
void FUN_004c9380()
{
	DAT_05b9d730 = DAT_05b9d724;
	DAT_05b9d72c = DAT_05b9d744;
}

// FUNCTION: SADX 0x004c93a0
void SetNextStageNumber(unsigned char stg, unsigned char act)
{
	DAT_05b9d748 = stg;
	DAT_05b9d770 = act;
}

// FUNCTION: SADX 0x004c93c0
void ChangeStageWithFadeOut(unsigned char stg, unsigned char act)
{
	SetChangeGameMode(3);
	DAT_05b9d748 = stg;
	DAT_05b9d770 = act;
}

// FUNCTION: SADX 0x004c9400
void FUN_004c9400()
{
	FUN_004c9380();
	DAT_05b9d724 = DAT_05b9d748;
	DAT_05b9d744 = DAT_05b9d770;
}

// FUNCTION: SADX 0x004c9430
int FUN_004c9430()
{
	return DAT_05b9d724 << 8 | DAT_05b9d744;
}

// FUNCTION: SADX 0x004c9450
unsigned short GetLastStageNumber()
{
	return (unsigned short)((DAT_05b9d730 << 8) | DAT_05b9d72c);
}

// FUNCTION: SADX 0x004c9470
unsigned short GetNextStageNumber()
{
	return (unsigned short)(((short)DAT_05b9d748 << 8) | (short)DAT_05b9d770);
}

// FUNCTION: SADX 0x004c9490
long NP_ChkStageChaoGarden()
{
	if ((short)DAT_05b9d724 == 0x27 || (short)DAT_05b9d724 == 0x29 || (short)DAT_05b9d724 == 0x28 || (short)DAT_05b9d724 == 0x2a)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004c94d0
void AdvanceAct(short ssActAddition)
{
	if (ChkGameMode() == 0)
	{
		return;
	}
	AdvanceActLocal(ssActAddition);
}

// STUB: SADX 0x004c94f0
void AdvanceActLocal(short ssActAddition)
{
}

// FUNCTION: SADX 0x004c9630
void SetEntranceNumber(signed char number)
{
	DAT_05b9d720 = number;
}

// FUNCTION: SADX 0x004c9640
signed char GetEntranceNumber()
{
	return (signed char)DAT_05b9d720;
}

// FUNCTION: SADX 0x004c9c90
void FUN_004c9c90()
{
	GM_SetNextAdventureStage(DAT_05b9d724, DAT_05b9d744);
}

// STUB: SADX 0x004c9cb0
long SetNextTrialStage()
{
	return (long)0;
}

// FUNCTION: SADX 0x004c9dc0
long ChkPause()
{
	long local_8;
	if (!((short)DAT_05b9d73c == 0x10 || (short)DAT_05b9d73c == 0x19))
	{
		local_8 = 0;
	}
	else
	{
		local_8 = 1;
	}
	return local_8;
}

// FUNCTION: SADX 0x004c9e00
long ChkGameMode()
{
	int local_8;

	if (DAT_05b9d73c != 0xf && DAT_05b9d73c != 4 && DAT_05b9d73c != 2)
	{
		local_8 = 0;
	}
	else
	{
		local_8 = 1;
	}
	return local_8;
}

// FUNCTION: SADX 0x004cac60
void MissionInit()
{
	if (GM_CheckMode() == 1)
	{
		SeqInitStage();
	}
	GameInit();
	InitMission();
	ADXTaskInit();
}

// FUNCTION: SADX 0x004cac90
unsigned short FUN_004cac90()
{
	unsigned short uVar1;
	uVar1 = 0;
	GameLoop_with_SyoriOchiTaisaku();
	DisplayScore();
	DisplayTimer();
	return uVar1;
}

// STUB: SADX 0x004cacc0
void FUN_004cacc0()
{
}

// FUNCTION: SADX 0x004caf50
long isMissionClearDisp()
{
	long local_8 = 0;
	if (DAT_05b3e05c == 0xa && DAT_05b3739a != 0)
	{
		local_8 = 1;
	}
	return local_8;
}
