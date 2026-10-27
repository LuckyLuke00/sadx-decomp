#include <string.h>

#include "decls.h"
#include <stdlib.h>
struct AlrRoot;
struct alifewk;
void AlrReal_checkGoal(struct AlrReal *___this);
long AlrReal_checkCommendation(struct AlrReal *___this);
int AlrFanFan_checkFanFan(struct AlrFanFan *___this);
static int AlrReal_onSonic(struct AlrReal *___this);
struct AlrData;
void AlrReal_raceEndAlr(struct AlrReal *___this);
void AlrReal_setRanking(struct AlrReal *___this);
struct task;
struct Alr;
void A_Life_for_ALR(struct task *);
enum eCourseNumDX AL_GetCourseNum();
int AlrReal_createChaoALR(struct AlrReal *___this);
int AlrReal_createChao(struct AlrReal *___this, int alr_or_alre_or_demo);
static void AlrReal_changeAct_for_Race(struct AlrReal *___this);
struct AlrReal;
extern struct AlrData alrdata;

extern struct AlrReal *DAT_05b33108;
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

#pragma optimize("", off)
// STUB: SADX 0x004826f0
void AlrReal_controlMode(struct AlrReal *___this)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00483070
static void AlrReal_changeAct_for_Race(struct AlrReal *___this)
{
}
#pragma optimize("", on)

// STUB: SADX 0x00483140
void AlrReal_changeAct_for_Entrance(struct AlrReal *___this)
{
}

// FUNCTION: SADX 0x00483240
int AlrReal_createChao(struct AlrReal *___this, int alr_or_alre_or_demo)
{

	switch (alr_or_alre_or_demo)
	{
	case 2:
		if (AlrReal_createChaoALR(___this) == 0)
		{
			return 0;
		}
		break;
	}
	return 1;
}

#pragma optimize("", off)
// STUB: SADX 0x00483270
int AlrReal_createChaoALR(struct AlrReal *___this)
{
	return (int)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004833e0
void A_Life_for_ALR(struct task *tp)
{
	ALR_Init(tp);
	*(void (**)(struct task *))((char *)tp + 0x10) = ALR_Executor;
	*(void (**)(struct task *))((char *)tp + 0x18) = ALR_Destructor;
}

#pragma optimize("", off)
// STUB: SADX 0x00483410
void AlrReal_setRanking(struct AlrReal *___this)
{
}
#pragma optimize("", on)

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

// STUB: SADX 0x00483500
void AlrReal_checkGoal(struct AlrReal *___this)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00483930
void AlrReal_raceEndAlr(struct AlrReal *___this)
{
}
#pragma optimize("", on)

// STUB: SADX 0x00483a00
void AlrReal_SetCameraMode(struct AlrReal *___this,int mode)
{
}

#pragma optimize("", off)
// STUB: SADX 0x00483a40
void AlrReal_controlCamera(struct AlrReal *___this)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00483f00
void AlrReal_incLook(struct AlrReal *___this)
{
 if(___this->flag&0x10) return;
 if(++___this->look>=8) ___this->look=0;
}

// FUNCTION: SADX 0x00483f50
void AlrReal_decLook(struct AlrReal *___this)
{
 if(___this->flag&0x10) return;
 if(--___this->look<0) ___this->look=7;
}

#pragma optimize("", off)
// STUB: SADX 0x00483fa0
void AlrReal_dspHead(struct AlrReal *___this)
{
}
#pragma optimize("", on)

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

// FUNCTION: SADX 0x004840e0
void AlrFanFan_clear(struct AlrFanFan *___this)
{
 ___this->timer=(float)((float)rand()/32768.0)*600.0+1200.0;
 ___this->mode=0;
 ___this->extra=0;
 ___this->hit=0;
 ___this->se_timing=0;
}

// FUNCTION: SADX 0x00484150
int AlrFanFan_checkFanFan(struct AlrFanFan *___this)
{
	if (!*(unsigned char *)((char *)___this + 2))
		return 0;
	return 1;
}

// FUNCTION: SADX 0x004849a0
void AlrReal_checkSaveJewel(struct AlrReal *___this)
{
 int local_8g;
 struct alifewk *local_cj;
 int local_10;
 ___this->flag &= ~0x100;
 if(!(___this->flag&0x20)) return;
 local_8g=AlrRank_GetId(&___this->alrrank,0);
 local_cj=Alr_GetAwp(&___this->alr[local_8g]);
 if(local_cj)
 {
  switch(AL_GetCourseNum())
  {
  case 0: local_10=0xb; break;
  case 1: local_10=0xc; break;
  case 2: local_10=0xf; break;
  case 3: local_10=0xe; break;
  case 4: local_10=0xd; break;
  }
  *(char *)(*(int *)((char *)local_cj->pAdv2ChaoTask->twp+0x6c)+0xd7)=local_10;
 }
}

// FUNCTION: SADX 0x00484a90
long AlrReal_checkCommendation(struct AlrReal *___this)
{
	if (*(unsigned char *)((char *)___this + 0x156e) >= 5 && *(unsigned char *)((char *)___this + 0x156e) <= 8)
	{
		return 1;
	}
	return 0;
}
