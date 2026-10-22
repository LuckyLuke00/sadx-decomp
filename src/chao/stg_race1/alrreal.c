#include <string.h>

#include "decls.h"
#include <stdlib.h>
extern int DAT_05b92e44;
extern int FUN_00484d90(struct AlrCam *param_1);
struct AlrRank;
struct AlrRoot;
struct alifewk;
struct AL_RECORD;
struct NJS_POINT3;
void AlrReal_checkGoal(struct AlrReal *___this);
static long AlrReal_checkCommendation(struct AlrReal *___this);
static int AlrFanFan_checkFanFan(struct AlrFanFan *___this);
static int AlrReal_onSonic(struct AlrReal *___this);
struct AlrData;
static void AlrReal_raceEndAlr(struct AlrReal *___this);
static void AlrReal_setRanking(struct AlrReal *___this);
struct task;
struct Alr;
void A_Life_for_ALR(struct task *);
struct task *CreateChao_for_ALR_ALRE(void (*)(struct task *), struct al_status *);
void *Alr_SetId(struct Alr *, int);
enum eCourseNumDX AL_GetCourseNum();
static int AlrReal_createChaoALR(struct AlrReal *___this);
static int AlrReal_createChao(struct AlrReal *___this, int alr_or_alre_or_demo);
static void AlrReal_changeAct_for_Race(struct AlrReal *___this);
struct AlrReal;
extern struct AlrData alrdata;

extern struct AlrReal *DAT_05b33108;
extern unsigned int *DAT_05b93264;
extern short DAT_05ccde90;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
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

// FUNCTION: SADX 0x00483140
void AlrReal_changeAct_for_Entrance(struct AlrReal *___this)
{
 int current;
 ___this->stimer = 0;
 AlrRank_Clear(&___this->alrrank);
 AlrTimer_Clear(&___this->alrtimer);
 AlrTimer_SetBest(&___this->alrtimer, ___this->alrmemory, AL_GetCourseNum());
 AlrReal_SetCameraMode(___this, 9);
 AlrRoot_Clear(&___this->alrroot, alrdata.endpathpos[AL_GetCourseNum()]);
 AlrFanFan_clear(&___this->alrfanfan);
 AlrReal_createChao(___this, 2);
 for (current=0; current<8; current++)
 {
  do { ___this->alr[current].mode=0xe; } while (0);
 }
 AlrObjFreeManageTask();
 do { ___this->mode=0; ___this->stimer=0; } while (0);
}

// FUNCTION: SADX 0x00483240
static int AlrReal_createChao(struct AlrReal *___this, int alr_or_alre_or_demo)
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

// FUNCTION: SADX 0x00483270
static int AlrReal_createChaoALR(struct AlrReal *___this)
{
 int current;
 int max_racer_id;
 int cpu_drive;
 const struct NJS_POINT3 *start;
 struct taskwk *twp;
 struct task *tp;
 cpu_drive=0;
 max_racer_id=-1;
 start=(const struct NJS_POINT3 *)((const char *)alrdata.startpos+AL_GetCourseNum()*0x60);
 for(current=0;current<8;current++)
 {
  tp=CreateChao_for_ALR_ALRE(A_Life_for_ALR,&___this->status[current]);
  if (___this->status[current].flag&2) max_racer_id=current;
  ___this->entry[current].id=current;
  if (*(unsigned char *)((char *)&___this->status[current]+0x17a)) ___this->entry[current].garden=4;
  else ___this->entry[current].garden=0;
  if(tp==0) return 0;
  twp=tp->twp;
  twp->pos=start[current];
  twp->value.ptr=Alr_SetId(&___this->alr[current],current);
  if(max_racer_id>=0)
  {
   do { ___this->alr[max_racer_id].flag |= 0x100; } while(0);
  }
 }
 return 1;
}

// FUNCTION: SADX 0x004833e0
void A_Life_for_ALR(struct task *tp)
{
	ALR_Init(tp);
	*(void (**)(struct task *))((char *)tp + 0x10) = ALR_Executor;
	*(void (**)(struct task *))((char *)tp + 0x18) = ALR_Destructor;
}

// FUNCTION: SADX 0x00483410
static void AlrReal_setRanking(struct AlrReal *___this)
{
 int local_8g;
 int local_cg;
 AlrRank_CalcRank(&___this->alrrank,___this->alr,___this->look);
 for(local_8g=0;local_8g<8;local_8g++)
 {
  local_cg=AlrRank_GetId(&___this->alrrank,local_8g);
  do { ___this->alr[local_cg].rank=local_8g; } while(0);
 }
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

// FUNCTION: SADX 0x00483500
void AlrReal_checkGoal(struct AlrReal *___this)
{
 char local_b0[0x38];
 unsigned long local_78h;
 unsigned long local_74i;
 char local_70g[0x38];
 unsigned long local_34h;
 unsigned long local_30r;
 struct AL_TIME *local_2cm;
 struct alifewk *local_28k;
 int local_24k;
 struct CHAO_PARAM_GC *local_20g;
 struct AL_TIME local_1cp;
 struct AlrEntry *local_18o;
 struct Alr *local_14s;
 int local_10l;
 int local_ci;
 float local_8g;
 local_8g=alrdata.endpathpos[AL_GetCourseNum()];
 local_10l=8-___this->entry_num;
 for(local_ci=0;local_ci<8;local_ci++)
 {
  local_14s=&___this->alr[local_ci];
  local_18o=&___this->entry[local_ci];
  if(local_14s->pathpos>local_8g && Alr_CheckRace(local_14s))
  {
   do { local_14s->mode=0x10; } while(0);
  }
  if(local_14s->mode==0x10)
  {
   if(AlrRoot_CheckGoal(&___this->alrroot,&local_14s->twp->pos))
   {
    do { local_14s->mode=0xa; } while(0);
    if(local_14s->rank==0)
    {
     CallGoalin();
     SetCommandToDialog(0,0xa);
     dsPlay_oneshot(0x563,0,0,0);
     ___this->tmp_look=___this->look;
     ___this->look=local_14s->id;
     AlrReal_SetCameraMode(___this,6);
    }
    if(local_18o->garden!=4)
    {
     if(AL_GetRaceNum()!=2)
     {
      do { ___this->mode=4; ___this->stimer=0; } while(0);
     }
     if(local_14s->rank==0)
     {
      local_24k=AlrRank_GetId(&___this->alrrank,0);
      local_28k=Alr_GetAwp(&___this->alr[local_24k]);
      local_20g=*(struct CHAO_PARAM_GC **)((char *)local_28k->pAdv2ChaoTask->twp+0x6c);
      local_1cp.frame=___this->alrtimer.current.timer[0];
      local_1cp.second=___this->alrtimer.current.timer[1];
      local_1cp.minute=___this->alrtimer.current.timer[2];
      local_2cm=&local_20g->raceDX.PersonalRecord[AL_GetCourseNum()];
      if(local_2cm->minute==0 && local_2cm->second==0 && local_2cm->frame==0)
      {
       memcpy(local_2cm,&local_1cp,3);
      }
      else
      {
       local_34h=local_1cp.minute*60*60+local_1cp.second*60+local_1cp.frame;
       local_30r=local_2cm->minute*60*60+local_2cm->second*60+local_2cm->frame;
       if(local_34h<local_30r) memcpy(local_2cm,&local_1cp,3);
      }
      AL_GetCourseRecord(AL_GetCourseNum(),(struct AL_RECORD *)local_70g);
      local_78h=local_1cp.minute*60*60+local_1cp.second*60+local_1cp.frame;
      local_74i=(unsigned char)local_70g[1]*60*60+(unsigned char)local_70g[2]*60+(unsigned char)local_70g[3];
      if(local_74i==0 || !local_70g[0] || local_78h<local_74i)
      {
       memcpy(local_b0+1,&local_1cp,3);
       local_b0[0]=1;
       AL_SetCourseRecord(AL_GetCourseNum(),(struct AL_RECORD *)local_b0);
      }
      if(AL_GetRaceNum()==0)
      {
       if(AL_GetCourseClearedLevel(AL_GetCourseNum())<0) AL_CourseClearedLevelUp(AL_GetCourseNum());
       if(AL_GetCourseNum()==4) AL_SetRaceNew((enum eRaceNum)1);
      }
      else if(AL_GetRaceNum()==1)
      {
       ___this->flag|=0x20;
       if(AL_GetCourseClearedLevel(AL_GetCourseNum())<1)
       {
        AL_CourseClearedLevelUp(AL_GetCourseNum());
        ___this->flag|=0x40;
       }
      }
     }
    }
   }
  }
  if(local_18o->garden!=4)
  {
   if(Alr_CheckGoal(local_14s)) local_10l++;
  }
 }
 if(local_10l==8)
 {
  do { ___this->mode=4; ___this->stimer=0; } while(0);
 }
}

// FUNCTION: SADX 0x00483930
static void AlrReal_raceEndAlr(struct AlrReal *___this)
{
 int current;
 float goal;
 struct Alr *alr;
 goal=alrdata.endpathpos[AL_GetCourseNum()];
 for(current=0;current<8;current++)
 {
  alr=&___this->alr[current];
  if(alr->pathpos>goal && Alr_CheckRace(alr))
  {
   do { alr->mode=0x10; } while(0);
  }
  if(alr->mode==0x10)
  {
   if(AlrRoot_CheckGoal(&___this->alrroot,&alr->twp->pos))
   {
    do { alr->mode=0xa; } while(0);
   }
  }
 }
}

// FUNCTION: SADX 0x00483a00
void AlrReal_SetCameraMode(struct AlrReal *___this,int mode)
{
 do {
  AlrCam_CheckAndRelease(&___this->alrcam);
  ___this->alrcam.mode=mode;
  ___this->alrcam.smode=0;
 } while(0);
 ___this->camera_timer=0;
}

// FUNCTION: SADX 0x00483a40
void AlrReal_controlCamera(struct AlrReal *___this)
{
 int cmode;
 cmode=FUN_00484d90(&___this->alrcam);
 if(0)
 {
  if(cmode!=0xc)
  {
   if(!DAT_05ccde90 && (DAT_05b93264[4]&0x400)) AlrReal_SetCameraMode(___this,0xc);
  }
  else
  {
   if(!DAT_05ccde90 && (DAT_05b93264[4]&0x400)) AlrReal_SetCameraMode(___this,9);
  }
 }
 if(0)
 {
  if(cmode!=0xb)
  {
   if(!DAT_05ccde90 && (DAT_05b93264[4]&0x400)) AlrReal_SetCameraMode(___this,0xb);
  }
  else
  {
   if(!DAT_05ccde90 && (DAT_05b93264[4]&0x400)) AlrReal_SetCameraMode(___this,9);
  }
 }
 if(___this->mode==5) AlrReal_SetCameraMode(___this,0xa);
 switch(cmode)
 {
 case 2: break;
 case 3:
  if(___this->camera_timer<45.0)
  {
   do { ___this->alr[___this->look].flag|=0x2000; } while(0);
  }
  break;
 case 4:
  if(___this->camera_timer>138.0) AlrReal_SetCameraMode(___this,9);
  break;
 case 9:
  if((___this->flag&0x10) || DAT_05ccde90) break;
  if(DAT_05b92e44&0x80) AlrReal_incLook(___this);
  if(DAT_05b92e44&0x40) AlrReal_decLook(___this);
  if(DAT_05b92e44&0x20) AlrReal_SetCameraMode(___this,5);
  break;
 case 5:
  if(Alr_GetCurrentEvent(&___this->alr[___this->look])==1) AlrCam_ConstraintAroundAng(&___this->alrcam,0);
  if((___this->flag&0x10) || DAT_05ccde90) break;
  if(DAT_05b92e44&0x80) { AlrReal_incLook(___this); ___this->camera_timer=0; }
  if(DAT_05b92e44&0x40) { AlrReal_decLook(___this); ___this->camera_timer=0; }
  if(DAT_05b92e44&0x10) AlrReal_SetCameraMode(___this,9);
  if(___this->camera_timer<108.0 && ___this->camera_timer>30.0)
  {
   do { ___this->alr[___this->look].flag|=0x2000; } while(0);
  }
  break;
 case 6:
  if(___this->camera_timer>150.0)
  {
   ___this->look=___this->tmp_look;
   AlrReal_SetCameraMode(___this,9);
  }
 case 7:
 case 8:
  if(___this->camera_timer<45.0)
  {
   do { ___this->alr[___this->look].flag|=0x2000; } while(0);
  }
  break;
 case 10:
  if(___this->camera_timer<180.0)
  {
   do { ___this->alr[*(unsigned char *)&___this->alrrank].flag|=0x2000; } while(0);
  }
  ___this->look=AlrRank_GetId(&___this->alrrank,0);
  break;
 }
 ___this->flag&=~0x10;
 ___this->camera_timer++;
}

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
		position.y = position.y + 8.0;
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
static int AlrFanFan_checkFanFan(struct AlrFanFan *___this)
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
static long AlrReal_checkCommendation(struct AlrReal *___this)
{
	if (*(unsigned char *)((char *)___this + 0x156e) >= 5 && *(unsigned char *)((char *)___this + 0x156e) <= 8)
	{
		return 1;
	}
	return 0;
}
