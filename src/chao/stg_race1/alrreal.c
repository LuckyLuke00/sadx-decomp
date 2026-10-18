#include <string.h>

#include "decls.h"

extern struct AlrReal *DAT_05b33108;
extern unsigned int *DAT_05b93264;
extern short DAT_05ccde90;
extern unsigned short DAT_05b9d724;
extern unsigned short DAT_05b9d744;
extern char DAT_05ccca18;
void FUN_004881d0(struct AlrTimer *param_1);
int FUN_00486bb0(struct Alr *param_1);
void FUN_00488c50(struct AlrMemory *param_1);
void FUN_004897f0(struct AlrRoot *param_1, struct pathtag **param_2, int param_3, float param_4);

// FUNCTION: SADX 0x00482320
int AlrReal_Exe(struct AlrReal *awp)
{
	AlrReal_exe_for_Race(awp);
	if (awp->total_timer != 0xffff)
	{
		awp->total_timer++;
	}
	else
	{
		awp->total_timer = 0;
	}
	if (awp->flag & 4)
	{
		awp->flag = awp->flag & ~4;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004823a0
void AlrReal_exe_for_Race(struct AlrReal *awp)
{
	int i;

	if (awp == 0)
	{
		return;
	}
	AlrReal_controlColliMode(awp);
	AlrReal_controlMode(awp);
	if (1 && (awp->flag & 1))
	{
		awp->flag = awp->flag & ~1;
		AlrReal_changeAct_for_Race(awp);
	}
	AlrReal_controlCamera(awp);
	for (i = 0; i < 8; i++)
	{
		Alr_Exe(&awp->alr[i], &awp->alrroot, AL_GetCourseNum());
	}
	AlrCam_Exe(&awp->alrcam, awp);
	AlrReal_Dsp(awp);
}

// FUNCTION: SADX 0x00482480
void AlrReal_Dsp(struct AlrReal *awp)
{
	AlrTimer_Dsp(&awp->alrtimer);
	AlrRank_Dsp(&awp->alrrank, awp->alr, awp->look);
	AlrReal_dspHead(awp);
}

// FUNCTION: SADX 0x004824d0
void AlrReal_Destructor(struct AlrReal *awp)
{
	if (awp == 0)
	{
		return;
	}
	DAT_05b33108 = 0;
	AlrRoot_Del(&awp->alrroot);
	AlrReal_onSonic(awp);
	WinDestructor();
	ClearPanel();
	Free(awp);
}

// FUNCTION: SADX 0x00482520
int GetChaoId(struct task *tp)
{
	int i;
	struct Alr *alr;
	struct alifewk *awp;
	struct task *chao;

	if (DAT_05b33108 && tp)
	{
		for (i = 0; i < 8; i++)
		{
			alr = &DAT_05b33108->alr[i];
			awp = Alr_GetAwp(alr);
			if (awp)
			{
				chao = awp->mytask;
				if (chao == tp)
				{
					return i;
				}
			}
		}
	}
	return -1;
}

// FUNCTION: SADX 0x004825a0
int FUN_004825a0(struct AlrReal *awp)
{
	int i;

	awp->entry_num = AL_GetnbPlayer();
	awp->look = 0;
	awp->average = 0.0f;
	awp->vms_lane = 0;
	awp->mode = 0;
	awp->stage_exe = AlrStage00_Exe;
	awp->total_timer = 0;
	awp->player = GetPlayerCharacterName(0);
	AlrCam_Ini(&awp->alrcam);
	FUN_004897f0(&awp->alrroot, pathdata_race, 2, alrdata.endpathpos[AL_GetCourseNum()]);
	awp->alrmemory = (struct AlrMemory *)ADV1_AL_GetRaceTimeRam();
	FUN_00488c50(awp->alrmemory);
	for (i = 0; i < 8; i++)
	{
		memcpy(&awp->status[i], ADV1_ALR_GetEntryStatus(i), 0x198);
	}
	AlrTimer_Clear(&awp->alrtimer);
	AlrRank_Clear(&awp->alrrank);
	AlrWhite_Init();
	return 1;
}

// FUNCTION: SADX 0x004826e0
void AlrReal_controlColliMode(struct AlrReal *awp)
{
	CL_ColPolListUpModeSetAll();
}

// FUNCTION: SADX 0x004826f0
void AlrReal_controlMode(struct AlrReal *awp)
{
	int i;
	struct Alr *alr;
	float dif;
	struct NJS_POINT3 pos;

	awp->stimer++;
	if (AlrReal_checkCommendation(awp) == 1)
	{
		for (i = 0; i < 8; i++)
		{
			Alr_ConstraintLookAt(&awp->alr[i], &alrdata.fixedposition[16]);
		}
	}
	switch (awp->mode)
	{
	case 0:
		AlrReal_SetCameraMode(awp, 3);
		awp->look = 0;
		AlrObjSetManageTask();
		AlrConfetti_Init();
		ObjectAlrCracker_Init();
		AlrReal_offSonic(awp);
		for (i = 0; i < 8; i++)
		{
			do
			{
				awp->alr[i].mode = 2;
			} while (0);
		}
		do
		{
			awp->mode = 2;
			awp->stimer = 0;
		} while (0);
		break;
	case 1:
		do
		{
			awp->mode = 2;
			awp->stimer = 0;
		} while (0);
		break;
	case 2:
		if (awp->stimer % 0x30 == 0x2f)
		{
			awp->look++;
			awp->camera_timer = 0;
		}
		if (awp->look >= 8)
		{
			awp->look = 0;
			AlrReal_SetCameraMode(awp, 4);
			for (i = 0; i < 8; i++)
			{
				do
				{
					awp->alr[i].mode = 8;
				} while (0);
			}
			CallStart();
			dsPlay_oneshot(0x2b2, 0, 0, 0);
			dsPlay_oneshot(0x562, 0, 0, 0);
			SetCommandToDialog(0, 9);
			awp->flag |= 0x800;
			do
			{
				awp->mode = 3;
				awp->stimer = 0;
			} while (0);
		}
		break;
	case 3:
		FUN_004881d0(&awp->alrtimer);
		if (1)
		{
			AlrFanFan_exe(&awp->alrfanfan, awp);
		}
		for (i = 0; i < 8; i++)
		{
			alr = &awp->alr[i];
			dif = alr->pathpos - awp->average;
			if (!Alr_CheckRace(alr))
			{
				continue;
			}
			if (dif > 160.0 && AlrFanFan_checkFanFan(&awp->alrfanfan) != 1)
			{
				if (alr->mode != 7 && alr->mode != 5)
				{
					do
					{
						alr->mode = 6;
					} while (0);
				}
			}
			else
			{
				if (alr->mode == 7 || (alr->mode == 5 && FUN_00486bb0(alr)))
				{
					do
					{
						alr->mode = 8;
					} while (0);
				}
			}
		}
		AlrReal_checkGoal(awp);
		awp->stage_exe(awp);
		if (awp->stimer > 36000)
		{
			do
			{
				awp->mode = 4;
				awp->stimer = 0;
			} while (0);
		}
		AlrReal_calcAverage(awp);
		AlrReal_setRanking(awp);
		if (0)
		{
			if (DAT_05b93264[4] & 2)
			{
				awp->flag |= 1;
			}
			if (DAT_05ccde90 == 0 && (DAT_05b93264[2] & 0x200))
			{
				do
				{
					awp->alr[awp->look].flag |= 0x4000;
				} while (0);
			}
		}
		break;
	case 4:
		AlrReal_raceEndAlr(awp);
		if (awp->stimer == 100)
		{
			AlrWhite_Out(0x24);
		}
		if (awp->stimer == 0x6e)
		{
			StopAdvaBGM();
		}
		if (awp->stimer > 168.0)
		{
			do
			{
				awp->mode = 5;
				awp->stimer = 0;
			} while (0);
			for (i = 0; i < 8; i++)
			{
				Alr_DisconnectObj(&awp->alr[i]);
				do
				{
					awp->alr[i].mode = 0xc;
				} while (0);
			}
		}
		break;
	case 5:
	{
		int top;

		MirenSoundStartBgm(0x11);
		ObjectAlrCracker_Start();
		if (awp->flag & 0x20)
		{
			do
			{
				pos.x = alrdata.fixedposition[8].x;
				pos.y = alrdata.fixedposition[8].y;
				pos.z = alrdata.fixedposition[8].z;
			} while (0);
			dsPlay_oneshot(0x564, 0, 0, 0);
			pos.y = pos.y + 10.0;
			Jewel_Create(AL_GetCourseNum(), &pos);
		}
		else if (AL_GetRaceNum() == 1)
		{
			if (!(*(int *)((char *)awp->alrmemory + 8) & AL_GetCourseNum()))
			{
				dsPlay_oneshot(0x565, 0, 0, 0);
			}
		}
		top = awp->alrrank.rank[0];
		if (awp->entry[top].garden != 4)
		{
			if (awp->flag & 0x40)
			{
				CallJewelGet();
				SetCommandToDialog(0, 0xb);
			}
			else
			{
				CallCool();
				SetCommandToDialog(0, 0xb);
			}
		}
		AlrWhite_In(0x30);
		AlrReal_checkSaveJewel(awp);
		awp->mode = 6;
		awp->scnt = 0;
		awp->stimer = 0;
	}
	case 6:
	{
		struct alifewk *life;
		struct AlrEntry *ent;

		do
		{
			if (awp->alr[awp->scnt].flag & 0x80)
			{
				do
				{
					awp->alr[awp->scnt].flag &= ~0x80;
				} while (0);
				ent = &awp->entry[awp->scnt];
				life = Alr_GetAwp(&awp->alr[awp->scnt]);
				if (ent->garden == 3 && life)
				{
					awp->mode = 7;
				}
				else
				{
					awp->flag |= 0x80;
				}
			}
			awp->scnt++;
			if (awp->scnt >= 8)
			{
				awp->mode = 8;
				break;
			}
		} while (1);
		break;
	}
	case 7:
		awp->mode = 6;
		break;
	case 8:
	{
		long stage;
		long name;
		int idx;

		if (DAT_05ccde90 != 0)
		{
			awp->stimer = 0;
		}
		if (awp->stimer < 2)
		{
			for (idx = 0; idx < 8; idx++)
			{
				AL_IconResetPos(awp->alr[idx].awp->pAdv2ChaoTask);
			}
		}
		if (awp->stimer > 540.0)
		{
			AllClearEntryDialog();
			if (awp->flag & 0x20)
			{
				name = GetPlayerCharacterName(0);
				stage = (((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744) >> 8;
				if (CheckEmblemofStageClear((struct SAVE_DATA *)&DAT_05ccca18, name, stage, AL_GetCourseNum()) != 1)
				{
					GetEmblemofStageClear((struct SAVE_DATA *)&DAT_05ccca18, name, stage, AL_GetCourseNum());
					InitGetEmblem();
					awp->stimer = 0;
					awp->mode = 9;
					if (isCheckGGApper_Emblem())
					{
						InitGGMessage();
					}
				}
				else
				{
					awp->flag |= 1;
					awp->mode++;
				}
			}
			else
			{
				awp->flag |= 1;
				awp->mode++;
			}
		}
		break;
	}
	case 9:
		if (awp->stimer > 300.0 && !isGGMessageEnable())
		{
			awp->flag |= 1;
			awp->mode++;
		}
		break;
	}
}
