#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern void (*DAT_05b9e0b0)();
extern enum eCHAO_STAGE_NUMBER ChaoOldStageNumber;
extern long ChaoExitStage;
extern enum eCHAO_STAGE_NUMBER ChaoStageNumber;
extern void *DAT_05b08844;
extern int DAT_05b9e064;
extern enum eCHAO_STAGE_NUMBER ChaoNextStageNumber;
void AL_ChangeStage(enum eCHAO_STAGE_NUMBER NextStage);
void FUN_00442520();
void PlayerEnable(unsigned char pno);
extern int DAT_05aeaa7c;

// GLOBAL: SADX 0x05aeaa78
static struct task *DAT_05aeaa78;
extern int DAT_05aeaa38;
extern struct task *DAT_05aeaa3c[15];
extern struct taskwk *DAT_05baf368[8];


// FUNCTION: SADX 0x0043e000
enum eCHAO_STAGE_NUMBER AL_GetStageNumber()
{
	return ChaoStageNumber;
}

// FUNCTION: SADX 0x0043e010
enum eCHAO_STAGE_NUMBER AL_GetPreStageNumber()
{
	return ChaoOldStageNumber;
}

// FUNCTION: SADX 0x0043e020
enum eCHAO_STAGE_NUMBER AL_GetNextStageNumber()
{
	return ChaoNextStageNumber;
}

// FUNCTION: SADX 0x0043e030
int FUN_0043e030()
{
	return ChaoStageNumber != ChaoNextStageNumber;
}

// FUNCTION: SADX 0x0043e050
void FUN_0043e050()
{
	if (DAT_05aeaa78)
	{
		*(char *)DAT_05aeaa78->twp = 0;
	}
}

// STUB: SADX 0x0043e060
void AL_CheckEggHold()
{
}

// FUNCTION: SADX 0x0043e110
static void AL_PlayerControlManager(struct task *tp)
{
	struct taskwk *var1;
	struct AL_ST_POS *var2;
	int var3;

	var1 = tp->twp;
	var3 = AL_GetPreStageNumber();
	if ((unsigned char)var1->mode <= 2)
	{
		switch (AL_GetStageNumber())
		{
		case 5:
			switch (var3)
			{
			case 3:
				var2 = &AL_StartPosEC_Odekake;
				break;
			case 4:
			case 6:
				var2 = &AL_StartPosEC_Warp;
				break;
			default:
				var2 = &AL_StartPosEC_EC;
				break;
			}
			break;
		case 6:
			switch (var3)
			{
			case 3:
				var2 = &AL_StartPosMR_Odekake;
				break;
			case 4:
			case 5:
				var2 = &AL_StartPosMR_Warp;
				break;
			default:
				var2 = &AL_StartPosMR_MR;
				break;
			}
			break;
		default:
			switch (var3)
			{
			case 5:
			case 6:
				var2 = &AL_StartPosSS_Warp;
				break;
			case 3:
				var2 = &AL_StartPosSS_Odekake;
				break;
			case 2:
				var2 = &AL_StartPosSS_Race;
				break;
			case 7:
				var2 = &AL_StartPosSS_Market;
				break;
			default:
				var2 = &AL_StartPosSS_SS;
				break;
			}
			break;
		}
		DAT_05baf368[0]->pos = var2->pos;
		DAT_05baf368[0]->ang.y = var2->angy;
		var1->mode++;
	}
}

// FUNCTION: SADX 0x0043e1f0
static void AL_PlayerControlManagerDestructor(struct task *tp)
{
	DAT_05aeaa78 = 0;
}

// FUNCTION: SADX 0x0043e200
void AL_CreatePlayerControlManager()
{
	if (DAT_05aeaa78)
	{
		FUN_0043e050();
	}
	else
	{
		struct task *var1 = CreateElementalTask(2, 0, AL_PlayerControlManager);
		DAT_05aeaa78 = var1;
		var1->dest = AL_PlayerControlManagerDestructor;
	}
}

// FUNCTION: SADX 0x0043e230
void FUN_0043e230()
{
	DAT_05aeaa38 = 0;
}

// FUNCTION: SADX 0x0043e240
void AL_WaitForSaveHookAdd(struct task *tp)
{
	DAT_05aeaa3c[DAT_05aeaa38] = tp;
	DAT_05aeaa38++;
}

// FUNCTION: SADX 0x0043e260
void AL_WaitForSaveHookRemove(struct task *tp)
{
	int var1;
	int var2;

	var2 = 0;
	for (var1 = 0; var1 < DAT_05aeaa38; var1++)
	{
		if (DAT_05aeaa3c[var1] != tp)
		{
			DAT_05aeaa3c[var2] = DAT_05aeaa3c[var1];
			var2++;
		}
	}
	DAT_05aeaa38 = var2;
}

// FUNCTION: SADX 0x0043e2a0
void AL_PlayerDisable()
{
	if (DAT_05aeaa7c == 0)
	{
		if (FUN_0043e030() == 0 || ChaoStageNumber == -1)
		{
			PlayerDisable(0);
			DAT_05aeaa7c = 1;
		}
	}
}

// FUNCTION: SADX 0x0043e2d0
void AL_PlayerEnable()
{
	if (DAT_05aeaa7c != 0)
	{
		PlayerEnable(0);
		DAT_05aeaa7c = 0;
	}
}

// FUNCTION: SADX 0x0043e420
void FUN_0043e420()
{
	FUN_004b6520((int)&texlist_al_icon);
	___OutputDebugString("ChaoMain Destructor\n");
	ALMC_Exit();
	AL_GBAManagerKill();
	FUN_00442520();
	AL_ReleaseModule((enum EChaoModuleEntry)2);
	AL_ReleaseModule((enum EChaoModuleEntry)1);
	AL_WaitForSaveHookRemove(DAT_05aeaa3c[8]);
	DAT_05aeaa3c[8] = 0;
}

// FUNCTION: SADX 0x0043e470
void StageMasterInit(struct task *tp)
{
	FUN_0043dff0();
	BGM_Stop();
	Serif_Stop();
	AL_InitLandMark();
	switch (ChaoStageNumber)
	{
	case 1:
		_alg_race_prolog();
		DAT_05b08844 = (void *)_alg_race_epilog;
		return;
	case 3:
		_al_odekake_prolog();
		DAT_05b08844 = (void *)_al_odekake_epilog;
		return;
	case 2:
		_alg_entrance_prolog();
		DAT_05b08844 = (void *)_alg_entrance_epilog;
		return;
	case 4:
		_alg_garden00_ss_prolog();
		DAT_05b08844 = (void *)_alg_garden00_ss_epilog;
		return;
	case 5:
		_alg_garden01_ec_prolog();
		DAT_05b08844 = (void *)_alg_garden01_ec_epilog;
		return;
	case 6:
		_alg_garden02_mr_prolog();
		DAT_05b08844 = (void *)_alg_garden02_mr_epilog;
		return;
	case 7:
		_alg_blackmarket_prolog();
		DAT_05b08844 = (void *)_alg_blackmarket_epilog;
		return;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0043e530
void AL_ChangeStage(enum eCHAO_STAGE_NUMBER NextStage)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0043e5f0
void AL_ChangeStageLater(enum eCHAO_STAGE_NUMBER NextStage)
{
	if (FUN_0043e030() == 0)
	{
		FUN_0043dfd0(NextStage);
		*(int *)(DAT_05aeaa3c + 4) = 1;
	}
}

// FUNCTION: SADX 0x0043e620
void AL_ExitToStage(long stage, long act)
{
	if (FUN_0043e030() == 0)
	{
		FUN_0043dfd0((enum eCHAO_STAGE_NUMBER)8);
		ChaoExitStage = stage;
		DAT_05aeaa3c[5] = (struct task *)act;
		FUN_0043fb50();
		if (DAT_05aeaa3c[8] != 0)
		{
			*(char *)(DAT_05aeaa3c[8]->twp) = 0xb;
		}
	}
}

// FUNCTION: SADX 0x0043e660
void _al_stage_epilog()
{
	___OutputDebugString("ChaoMain Epilog begin\n");
	if (DAT_05aeaa3c[7] != 0)
	{
		FUN_0043e420();
		DAT_05aeaa3c[7] = 0;
	}
	FUN_007d21b0();
	FUN_005b5aa0();
	ChaoOldStageNumber = (enum eCHAO_STAGE_NUMBER)-1;
	ChaoStageNumber = (enum eCHAO_STAGE_NUMBER)-1;
	ChaoNextStageNumber = (enum eCHAO_STAGE_NUMBER)-1;
	ChaoExitStage = -1;
	DAT_05aeaa3c[4] = 0;
	DAT_05aeaa3c[5] = 0;
	DAT_05b9e064 = (int)DAT_05aeaa3c[6];
	njControl3D((unsigned long)DAT_05aeaa3c[6]);
	___OutputDebugString("ChaoMain Epilog end\n");
}

// FUNCTION: SADX 0x0043e6e0
void FUN_0043e6e0()
{
	if (DAT_05aeaa3c[4])
	{
		DAT_05aeaa3c[4] = NULL;
		AL_ChangeStage(ChaoNextStageNumber);
	}
}

// FUNCTION: SADX 0x0043e990
void AL_ReturnStage()
{
	AL_ChangeStage(AL_GetPreStageNumber());
}

// FUNCTION: SADX 0x0043e9a0
void AL_ExitChaoGarden()
{
	AL_ExitToStage(-1, 0);
}

// FUNCTION: SADX 0x0043e9b0
void _al_stage_prolog()
{
	___OutputDebugString("ChaoMain Prolog begin\n");
	SaveControl3D();
	DAT_05aeaa3c[6] = (struct task *)DAT_05b9e064;
	FUN_00440050();
	DAT_05aeaa3c[7] = 0;
	DAT_05aeaa3c[14] = 0;
	FUN_005b5aa0();
	FUN_007d21b0();
	{
		unsigned short var1 = (DAT_05b9d724 << 8) | DAT_05b9d744;
		LandClearLandTable((long)(var1 >> 8), (long)(var1 & 0xff));
	}
	___OutputDebugString("ChaoMain Prolog end\n");
	DAT_05b9e0b0 = _al_stage_epilog;
}
