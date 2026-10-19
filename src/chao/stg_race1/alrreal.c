#include <string.h>

#include "decls.h"
#include <stdlib.h>
struct AlrRank;
struct AlrRoot;
struct NJS_POINT3;
extern double DAT_0095b120;
static long AlrReal_checkCommendation(struct AlrReal *___this);
static int AlrFanFan_checkFanFan(struct AlrFanFan *___this);
static int AlrReal_onSonic(struct AlrReal *___this);
struct AlrData;
struct task;
struct Alr;
void A_Life_for_ALR(struct task *);
enum eCourseNumDX AL_GetCourseNum();
static void AlrReal_changeAct_for_Race(struct AlrReal *___this);
struct AlrReal;
extern struct AlrData alrdata;

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
int AlrReal_Exe(struct AlrReal *___this)
{
	AlrReal_exe_for_Race(___this);
	if (___this->total_timer != 0xffff)
	{
		___this->total_timer++;
	}
	else
	{
		___this->total_timer = 0;
	}
	if (___this->flag & 4)
	{
		___this->flag = ___this->flag & ~4;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004823a0
void AlrReal_exe_for_Race(struct AlrReal *___this)
{
	int cnt;

	if (___this == 0)
	{
		return;
	}
	AlrReal_controlColliMode(___this);
	AlrReal_controlMode(___this);
	if (1 && (___this->flag & 1))
	{
		___this->flag = ___this->flag & ~1;
		AlrReal_changeAct_for_Race(___this);
	}
	AlrReal_controlCamera(___this);
	for (cnt = 0; cnt < 8; cnt++)
	{
		Alr_Exe(&___this->alr[cnt], &___this->alrroot, AL_GetCourseNum());
	}
	AlrCam_Exe(&___this->alrcam, ___this);
	AlrReal_Dsp(___this);
}

// FUNCTION: SADX 0x00482480
void AlrReal_Dsp(struct AlrReal *___this)
{
	AlrTimer_Dsp(&___this->alrtimer);
	AlrRank_Dsp(&___this->alrrank, ___this->alr, ___this->look);
	AlrReal_dspHead(___this);
}

// FUNCTION: SADX 0x004824d0
void AlrReal_Destructor(struct AlrReal *___this)
{
	if (___this == 0)
	{
		return;
	}
	DAT_05b33108 = 0;
	AlrRoot_Del(&___this->alrroot);
	AlrReal_onSonic(___this);
	WinDestructor();
	ClearPanel();
	Free(___this);
}

// FUNCTION: SADX 0x00482520
int GetChaoId(struct task *tp)
{
	int current;
	struct Alr *alr;
	struct alifewk *local_10g;
	struct task *local_14i;

	if (DAT_05b33108 && tp)
	{
		for (current = 0; current < 8; current++)
		{
			alr = &DAT_05b33108->alr[current];
			local_10g = Alr_GetAwp(alr);
			if (local_10g)
			{
				local_14i = local_10g->mytask;
				if (local_14i == tp)
				{
					return current;
				}
			}
		}
	}
	return -1;
}

// FUNCTION: SADX 0x004825a0
int FUN_004825a0(struct AlrReal *param_1)
{
	int local_8;

	param_1->entry_num = AL_GetnbPlayer();
	param_1->look = 0;
	param_1->average = 0.0f;
	param_1->vms_lane = 0;
	param_1->mode = 0;
	param_1->stage_exe = AlrStage00_Exe;
	param_1->total_timer = 0;
	param_1->player = GetPlayerCharacterName(0);
	AlrCam_Ini(&param_1->alrcam);
	FUN_004897f0(&param_1->alrroot, pathdata_race, 2, alrdata.endpathpos[AL_GetCourseNum()]);
	param_1->alrmemory = (struct AlrMemory *)ADV1_AL_GetRaceTimeRam();
	FUN_00488c50(param_1->alrmemory);
	for (local_8 = 0; local_8 < 8; local_8++)
	{
		memcpy(&param_1->status[local_8], ADV1_ALR_GetEntryStatus(local_8), 0x198);
	}
	AlrTimer_Clear(&param_1->alrtimer);
	AlrRank_Clear(&param_1->alrrank);
	AlrWhite_Init();
	return 1;
}

// FUNCTION: SADX 0x004826e0
void AlrReal_controlColliMode(struct AlrReal *___this)
{
	CL_ColPolListUpModeSetAll();
}

// FUNCTION: SADX 0x004826f0
void AlrReal_controlMode(struct AlrReal *___this)
{
	int local_8g;
	struct Alr *local_cj;
	float local_10;
	struct NJS_POINT3 local_20;

	___this->stimer++;
	if (AlrReal_checkCommendation(___this) == 1)
	{
		for (local_8g = 0; local_8g < 8; local_8g++)
		{
			Alr_ConstraintLookAt(&___this->alr[local_8g], &alrdata.fixedposition[16]);
		}
	}
	switch (___this->mode)
	{
	case 0:
		AlrReal_SetCameraMode(___this, 3);
		___this->look = 0;
		AlrObjSetManageTask();
		AlrConfetti_Init();
		ObjectAlrCracker_Init();
		AlrReal_offSonic(___this);
		for (local_8g = 0; local_8g < 8; local_8g++)
		{
			do
			{
				___this->alr[local_8g].mode = 2;
			} while (0);
		}
		do
		{
			___this->mode = 2;
			___this->stimer = 0;
		} while (0);
		break;
	case 1:
		do
		{
			___this->mode = 2;
			___this->stimer = 0;
		} while (0);
		break;
	case 2:
		if (___this->stimer % 0x30 == 0x2f)
		{
			___this->look++;
			___this->camera_timer = 0;
		}
		if (___this->look >= 8)
		{
			___this->look = 0;
			AlrReal_SetCameraMode(___this, 4);
			for (local_8g = 0; local_8g < 8; local_8g++)
			{
				do
				{
					___this->alr[local_8g].mode = 8;
				} while (0);
			}
			CallStart();
			dsPlay_oneshot(0x2b2, 0, 0, 0);
			dsPlay_oneshot(0x562, 0, 0, 0);
			SetCommandToDialog(0, 9);
			___this->flag |= 0x800;
			do
			{
				___this->mode = 3;
				___this->stimer = 0;
			} while (0);
		}
		break;
	case 3:
		FUN_004881d0(&___this->alrtimer);
		if (1)
		{
			AlrFanFan_exe(&___this->alrfanfan, ___this);
		}
		for (local_8g = 0; local_8g < 8; local_8g++)
		{
			local_cj = &___this->alr[local_8g];
			local_10 = local_cj->pathpos - ___this->average;
			if (!Alr_CheckRace(local_cj))
			{
				continue;
			}
			if (local_10 > 160.0 && AlrFanFan_checkFanFan(&___this->alrfanfan) != 1)
			{
				if (local_cj->mode != 7 && local_cj->mode != 5)
				{
					do
					{
						local_cj->mode = 6;
					} while (0);
				}
			}
			else
			{
				if (local_cj->mode == 7 || (local_cj->mode == 5 && FUN_00486bb0(local_cj)))
				{
					do
					{
						local_cj->mode = 8;
					} while (0);
				}
			}
		}
		AlrReal_checkGoal(___this);
		___this->stage_exe(___this);
		if (___this->stimer > 36000)
		{
			do
			{
				___this->mode = 4;
				___this->stimer = 0;
			} while (0);
		}
		AlrReal_calcAverage(___this);
		AlrReal_setRanking(___this);
		if (0)
		{
			if (DAT_05b93264[4] & 2)
			{
				___this->flag |= 1;
			}
			if (DAT_05ccde90 == 0 && (DAT_05b93264[2] & 0x200))
			{
				do
				{
					___this->alr[___this->look].flag |= 0x4000;
				} while (0);
			}
		}
		break;
	case 4:
		AlrReal_raceEndAlr(___this);
		if (___this->stimer == 100)
		{
			AlrWhite_Out(0x24);
		}
		if (___this->stimer == 0x6e)
		{
			StopAdvaBGM();
		}
		if (___this->stimer > 168.0)
		{
			do
			{
				___this->mode = 5;
				___this->stimer = 0;
			} while (0);
			for (local_8g = 0; local_8g < 8; local_8g++)
			{
				Alr_DisconnectObj(&___this->alr[local_8g]);
				do
				{
					___this->alr[local_8g].mode = 0xc;
				} while (0);
			}
		}
		break;
	case 5:
	{
		int local_24;

		MirenSoundStartBgm(0x11);
		ObjectAlrCracker_Start();
		if (___this->flag & 0x20)
		{
			do
			{
				local_20.x = alrdata.fixedposition[8].x;
				local_20.y = alrdata.fixedposition[8].y;
				local_20.z = alrdata.fixedposition[8].z;
			} while (0);
			dsPlay_oneshot(0x564, 0, 0, 0);
			local_20.y = local_20.y + 10.0;
			Jewel_Create(AL_GetCourseNum(), &local_20);
		}
		else if (AL_GetRaceNum() == 1)
		{
			if (!(*(int *)((char *)___this->alrmemory + 8) & AL_GetCourseNum()))
			{
				dsPlay_oneshot(0x565, 0, 0, 0);
			}
		}
		local_24 = ___this->alrrank.rank[0];
		if (___this->entry[local_24].garden != 4)
		{
			if (___this->flag & 0x40)
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
		AlrReal_checkSaveJewel(___this);
		___this->mode = 6;
		___this->scnt = 0;
		___this->stimer = 0;
	}
	case 6:
	{
		struct alifewk *awp;
		struct AlrEntry *entry;

		do
		{
			if (___this->alr[___this->scnt].flag & 0x80)
			{
				do
				{
					___this->alr[___this->scnt].flag &= ~0x80;
				} while (0);
				entry = &___this->entry[___this->scnt];
				awp = Alr_GetAwp(&___this->alr[___this->scnt]);
				if (entry->garden == 3 && awp)
				{
					___this->mode = 7;
				}
				else
				{
					___this->flag |= 0x80;
				}
			}
			___this->scnt++;
			if (___this->scnt >= 8)
			{
				___this->mode = 8;
				break;
			}
		} while (1);
		break;
	}
	case 7:
		___this->mode = 6;
		break;
	case 8:
	{
		long local_38;
		long local_34;
		int local_30;

		if (DAT_05ccde90 != 0)
		{
			___this->stimer = 0;
		}
		if (___this->stimer < 2)
		{
			for (local_30 = 0; local_30 < 8; local_30++)
			{
				AL_IconResetPos(___this->alr[local_30].awp->pAdv2ChaoTask);
			}
		}
		if (___this->stimer > 540.0)
		{
			AllClearEntryDialog();
			if (___this->flag & 0x20)
			{
				local_34 = GetPlayerCharacterName(0);
				local_38 = (((short)DAT_05b9d724 << 8) | (short)DAT_05b9d744) >> 8;
				if (CheckEmblemofStageClear((struct SAVE_DATA *)&DAT_05ccca18, local_34, local_38, AL_GetCourseNum()) != 1)
				{
					GetEmblemofStageClear((struct SAVE_DATA *)&DAT_05ccca18, local_34, local_38, AL_GetCourseNum());
					InitGetEmblem();
					___this->stimer = 0;
					___this->mode = 9;
					if (isCheckGGApper_Emblem())
					{
						InitGGMessage();
					}
				}
				else
				{
					___this->flag |= 1;
					___this->mode++;
				}
			}
			else
			{
				___this->flag |= 1;
				___this->mode++;
			}
		}
		break;
	}
	case 9:
		if (___this->stimer > 300.0 && !isGGMessageEnable())
		{
			___this->flag |= 1;
			___this->mode++;
		}
		break;
	}
}

// FUNCTION: SADX 0x00483070
static void AlrReal_changeAct_for_Race(struct AlrReal *___this)
{
	int current;

	*(short *)((char *)___this + 0x157e) = 0;
	AlrRank_Clear((struct AlrRank *)((char *)___this + 0x14c0));
	AlrRoot_Clear((struct AlrRoot *)((char *)___this + 0x1500), (*(float **)((char *)&alrdata + 8))[AL_GetCourseNum()]);
	AlrObjFreeManageTask();
	for (current = 0; current < 8; current++)
	{
		Alr_Kill((struct Alr *)((char *)___this + 0xcc0 + current * 0xf4));
	}
	for (current = 0; current < 8; current++)
	{
	}
	AlrReal_onSonic(___this);
	*(unsigned short *)((char *)___this + 0x157c) |= 4;
}

// FUNCTION: SADX 0x004833e0
void A_Life_for_ALR(struct task *tp)
{
	ALR_Init(tp);
	*(void (**)(struct task *))((char *)tp + 0x10) = ALR_Executor;
	*(void (**)(struct task *))((char *)tp + 0x18) = ALR_Destructor;
}

// FUNCTION: SADX 0x00483490
void AlrReal_calcAverage(struct AlrReal *___this)
{
	int current;

	*(float *)((char *)___this + 0x1574) = 0.0f;
	for (current = 0; current < 8; current++)
	{
		*(float *)((char *)___this + 0x1574) += *(float *)((char *)___this + current * 0xf4 + 0xd90);
	}
	*(float *)((char *)___this + 0x1574) *= 0.125f;
}

// FUNCTION: SADX 0x00483fa0
void AlrReal_dspHead(struct AlrReal *___this)
{
	struct Alr *alr;
	struct taskwk *twp;
	NJS_POINT3 position;

	if (AlrReal_checkCommendation(___this) == 1)
	{
		return;
	}
	alr = (struct Alr *)((char *)___this + 0xcc0 + *(char *)((char *)___this + 0x156c) * 0xf4);
	twp = Alr_GetTwp(alr);
	if (twp)
	{
		do
		{
			position.x = *(float *)((char *)twp + 0x20);
			position.y = *(float *)((char *)twp + 0x24);
			position.z = *(float *)((char *)twp + 0x28);
		} while (0);
		position.y = position.y + DAT_0095b120;
		AlrRank_DspHeadYa((struct AlrRank *)((char *)___this + 0x14c0), *(char *)((char *)___this + 0x156c) + 1, &position);
	}
}

// FUNCTION: SADX 0x00484060
int AlrReal_offSonic(struct AlrReal *___this)
{
	if ((*(unsigned short *)((char *)___this + 0x157c) & 2) == 0)
	{
		*(unsigned short *)((char *)___this + 0x157c) = *(unsigned short *)((char *)___this + 0x157c) | 2;
		AL_PlayerDisable();
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004840a0
static int AlrReal_onSonic(struct AlrReal *___this)
{
	if (*(unsigned short *)((char *)___this + 0x157c) & 2)
	{
		*(unsigned short *)((char *)___this + 0x157c) &= ~2;
		AL_PlayerEnable();
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00484150
static int AlrFanFan_checkFanFan(struct AlrFanFan *___this)
{
	if (!*(unsigned char *)((char *)___this + 2))
		return 0;
	return 1;
}

// FUNCTION: SADX 0x00484a90
static long AlrReal_checkCommendation(struct AlrReal *___this)
{
	if (*(unsigned char *)((char *)___this + 0x156e) >= 5 && *(unsigned char *)((char *)___this + 0x156e) <= 8)
	{
		return 1;
	}
	return 0;
}
