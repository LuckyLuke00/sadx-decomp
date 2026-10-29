#include "decls.h"
extern int DAT_05cd0f24;
void SeqNext();
extern char DAT_05bafb83;
extern char DAT_05bafb84;
extern char DAT_05bafb8d;
extern unsigned char DAT_05bafc87;
extern unsigned char DAT_05bafc89;
extern int DAT_05ccde10;
void dsLoadEVBossSound();
struct task *GetPlayerTaskPointer(unsigned char pno);
void FreeTask(struct task *tp);
struct task *EV_CreateBossPlayerTask(struct BOSSPLAYER_CREATE_PARAM *Param);
struct task *EV_CreateBossController(struct BOSSPLAYER_CREATE_PARAM *Param);
extern int last_eventlist[16];
extern void SetStageNumber(unsigned char stg, unsigned char act);
extern void SetEntranceNumber(signed char number);
void FUN_005b5aa0(...);
extern int DAT_05cd14d4;
void SeqTaskFadeOut(struct task *tp);
void SeqTaskFadeIn(struct task *tp);
void SeqCtrl();
long FUN_004f4bb0();
long GetPlayerNumber();
void SeqResetLastScenario();
void EventBossExecutor(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern char DAT_05baf548[];
void FUN_004f4b70(void);
void SeqPlayable(long playerno);
void ADX_Close();
void EV_PcNpcEnd();
void plboss_destruct(struct task *tp);
extern char DAT_05baf548[0x2b * 4];
extern int slEventBossName;
extern unsigned short plboss_name[6];
extern int DAT_05baf538;
extern unsigned short plboss_equ[6][2];
extern struct BOSSPLAYER_CREATE_PARAM DAT_05bafd1c;
extern unsigned char DAT_05bafb00[];
extern unsigned char DAT_05bafb41;
extern unsigned char DAT_05bafb42;
extern unsigned char DAT_05bafb43;
extern unsigned char DAT_05bafb44;
extern unsigned char DAT_05bafb45;
extern unsigned char DAT_05bafb46;
extern int DAT_05cd0f28;
void SeqSave();
extern int DAT_05baf53c;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_05cc3574;
extern char DAT_05cc3631;
extern unsigned char DAT_05bb00a8;
extern short DAT_05bafd18;
extern int DAT_05baf544;
void FUN_004f5550(int param_1);
extern long slSeqRunning;
extern int DAT_05b3ea28;
extern signed char DAT_05baf900[0x200];
struct SEQUENCE {
	signed char time;
	signed char emerald;
	short seqno;
	short sec;
	short nextsec;
	unsigned short stage;
	unsigned short destination;
};
// GLOBAL: SADX 0x05baf6a0
struct SEQUENCE DAT_05baf6a0[8];
extern int DAT_05bafd4c;

// STUB: SADX 0x004f49f0
void SeqInit()
{
}

// FUNCTION: SADX 0x004f4b70
void FUN_004f4b70(void)
{
	DAT_05b3ea28 = 0;
	DAT_05bafd4c = 0;
}

// FUNCTION: SADX 0x004f4b90
void SeqRun()
{
	slSeqRunning = 1;
}

// FUNCTION: SADX 0x004f4ba0
void SeqStop()
{
	slSeqRunning = 0;
}

// FUNCTION: SADX 0x004f4bb0
long FUN_004f4bb0()
{
	return slSeqRunning;
}

// FUNCTION: SADX 0x004f4bc0
void SeqSetPlayer(int no)
{
	if (FUN_004f4bb0() == 0)
	{
		return;
	}
	if (DAT_05bb00a8 != 0)
	{
		FUN_004f5550(0x58);
		DAT_05bafd18 = 4;
	}
	else
	{
		SeqClrFlag(0x58);
		DAT_05bafd18 = (short)no;
	}
	DAT_05b3ea28 = (int)&DAT_05baf6a0[DAT_05bafd18];
	DAT_05baf544 = (int)SeqGetSectionList(DAT_05bafd18);
}

// FUNCTION: SADX 0x004f4c40
void SeqSetSection(int sec)
{
	if (FUN_004f4bb0() == 0)
		return;
	if (DAT_05baf544 == 0)
		return;
	if (*(short *)((char *)DAT_05b3ea28 + 2) == 0 && *(short *)((char *)DAT_05b3ea28 + 4) == 0)
	{
		int local_8 = *(short *)((char *)DAT_05b3ea28 + 4) * 0x28 + DAT_05baf544;
		SetEntranceNumber(*(signed char *)((char *)local_8 + 6));
		SetStageNumber(*(unsigned char *)((char *)local_8 + 4), *(unsigned char *)((char *)local_8 + 5));
		*(short *)((char *)DAT_05b3ea28 + 8) = (short)((*(unsigned char *)((char *)local_8 + 4) << 8) | *(unsigned char *)((char *)local_8 + 5));
		*(short *)((char *)DAT_05b3ea28 + 6) = *(short *)((char *)local_8 + 6);
		*(short *)((char *)DAT_05b3ea28 + 10) = (short)((DAT_05b9d724 << 8) | DAT_05b9d744);
	}
	else if (*(short *)((char *)DAT_05b3ea28 + 4) < 0)
	{
		if (DAT_05bafd18 == 4)
		{
			SeqResetLastScenario();
		}
		else
		{
			SetEntranceNumber(0);
			SetStageNumber(0x1a, 3);
		}
	}
	else
	{
		SetStageNumber((unsigned char)((*(unsigned short *)((char *)DAT_05b3ea28 + 8)) >> 8), (unsigned char)((*(unsigned short *)((char *)DAT_05b3ea28 + 8)) & 0xff));
		SetEntranceNumber(*(signed char *)((char *)DAT_05b3ea28 + 6));
	}
	slEventBossName = 0xffffffff;
	if (GetPlayerNumber() == 0 && (unsigned char)DAT_05bafb83 == 1 && (unsigned char)DAT_05bafb84 == 0 && (unsigned char)DAT_05bafb8d == 1)
	{
		SetEntranceNumber(0);
		SetStageNumber(0x1a, 2);
	}
	if (GetPlayerNumber() == 6 && DAT_05bafc87 == 0 && DAT_05bafc89 == 1)
	{
		SetEntranceNumber(0);
		SetStageNumber(0x20, 0);
	}
}

// STUB: SADX 0x004f4e10
void SeqInitStage()
{
}

// STUB: SADX 0x004f4f20
int chk_advstage()
{
	return (int)0;
}

// STUB: SADX 0x004f4fe0
void SeqCtrl()
{
}

// FUNCTION: SADX 0x004f51d0
void SeqSave()
{
	if (DAT_05b3ea28 != 0)
	{
		*(short *)(DAT_05b3ea28 + 8) = (short)(DAT_05b9d724 << 8 | DAT_05b9d744);
		*(short *)(DAT_05b3ea28 + 6) = GetEntranceNumber();
		if (DAT_05cc3574 == 0)
		{
			DAT_05cc3631 = 1;
		}
		else
		{
			CreateSaveData();
		}
	}
}

// FUNCTION: SADX 0x004f5230
void SeqNext()
{
	if (*(short *)(DAT_05b3ea28 + 2) < 0)
	{
		return;
	}
	if (DAT_05baf53c != 0)
	{
		return;
	}
	(*(short *)(DAT_05b3ea28 + 2))++;
}

// STUB: SADX 0x004f5270
void SeqEndSection()
{
}

// STUB: SADX 0x004f52e0
void SeqEvent(long no)
{
}

// FUNCTION: SADX 0x004f5400
void SeqSetTime(long time)
{
	if (DAT_05b3ea28 != 0)
	{
		*(char *)DAT_05b3ea28 = (char)time;
	}
}

// FUNCTION: SADX 0x004f5420
long SeqGetTime()
{
	if (DAT_05b3ea28 == 0)
	{
		if (DAT_05cd0f28 == 0x12)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return *(char *)DAT_05b3ea28;
}

// FUNCTION: SADX 0x004f5450
long SeqCheckPlayable(long playerno)
{
	switch (playerno)
	{
		case 0:
			return DAT_05bafb41;
		case 2:
			return DAT_05bafb42;
		case 3:
			return DAT_05bafb43;
		case 5:
			return DAT_05bafb44;
		case 6:
			return DAT_05bafb45;
		case 7:
			return DAT_05bafb46;
	}
	return 0;
}

// FUNCTION: SADX 0x004f54d0
void SeqPlayable(long playerno)
{
	switch (playerno)
	{
		case 0:
			DAT_05bafb41 = 1;
			break;
		case 2:
			DAT_05bafb42 = 1;
			break;
		case 3:
			DAT_05bafb43 = 1;
			break;
		case 5:
			DAT_05bafb44 = 1;
			break;
		case 6:
			DAT_05bafb45 = 1;
			break;
		case 7:
			DAT_05bafb46 = 1;
			break;
	}
}

// FUNCTION: SADX 0x004f5550
void FUN_004f5550(int param_1)
{
	DAT_05bafb00[param_1] = 1;
}

// FUNCTION: SADX 0x004f5560
void SeqClrFlag(long no)
{
	DAT_05bafb00[no] = 0;
}

// FUNCTION: SADX 0x004f5570
long SeqCheckFlag(long no)
{
	return (long)((unsigned char)*(unsigned char *)(DAT_05bafb00 + no) != 0);
}

// FUNCTION: SADX 0x004f5590
long SeqCheckStage(long stg, long act)
{
	int local_8g;
	local_8g = (stg << 8) | act;
	if (((DAT_05b9d724 << 8) | DAT_05b9d744) != local_8g)
	{
		*(short *)(DAT_05b3ea28 + 0xa) = (short)local_8g;
		return 0;
	}
	return 1;
}

// FUNCTION: SADX 0x004f55e0
void SeqChangeStage(long stg, long act)
{
	ChangeStageWithFadeOut((unsigned char)stg, (unsigned char)act);
}

// FUNCTION: SADX 0x004f5600
long SeqCheckNextStage(unsigned char stg, unsigned char act)
{
	*(unsigned short *)(DAT_05b3ea28 + 0xa) = 0xffff;
	return GetNextStageNumber() == ((stg << 8) | act);
}

// FUNCTION: SADX 0x004f5640
void EventBossExecutor(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	switch (local_8->mode)
	{
		case 0:
			ADX_Close();
			EV_PcNpcEnd();
			dsLoadEVBossSound();
			local_8->mode = 1;
		case 1:
			if (GetPlayerTaskPointer(0) != 0)
			{
				DAT_05bafd1c.type = (enum EVBOSS_TYPE)plboss_equ[DAT_05baf538][0];
				DAT_05bafd1c.player_tp = GetPlayerTaskPointer(0);
				DAT_05bafd1c.boss_tp = 0;
				DAT_05bafd1c.exec = 0;
				DAT_05bafd1c.exit = plboss_destruct;
				EV_CreateBossPlayerTask(&DAT_05bafd1c);
				EV_CreateBossController(&DAT_05bafd1c);
				local_8->mode = 2;
			}
			break;
		case 2:
			local_8->mode = 3;
			break;
		case 3:
			FreeTask(tp);
			break;
	}
}

// FUNCTION: SADX 0x004f5720
void plboss_destruct(struct task *tp)
{
	ADX_Close();
	if (GetBossPlayerResult() == 1)
	{
		FUN_004f5550(plboss_equ[DAT_05baf538][1]);
		slEventBossName = 0xffffffff;
	}
	EV_FreeBossPlayerTask(&DAT_05bafd1c);
	dsReloadEVBossSound();
}

// FUNCTION: SADX 0x004f5770
void SeqExecBossPlayer(long type)
{
	slEventBossName = plboss_name[type];
	DAT_05baf538 = type;
	CreateElementalTask(2, 1, EventBossExecutor);
}

// FUNCTION: SADX 0x004f57a0
long SeqCheckClearAction(long stg)
{
	return DAT_05baf548[GetPlayerNumber() * 0x2b + stg] != 0;
}

// FUNCTION: SADX 0x004f57c0
void SeqSetClearActionFlag(long stg)
{
	struct SEQ_CLEAR_EQUIV *local_8;

	local_8 = actionEquivTable[GetPlayerNumber()];
	while (local_8->stageno != -1)
	{
		if (local_8->stageno == stg)
		{
			FUN_004f5550(local_8->flagno);
			return;
		}
		local_8 = (struct SEQ_CLEAR_EQUIV *)((char *)local_8 + 4);
	}
}

// FUNCTION: SADX 0x004f5810
long CheckEggCarrierInTheSea(void)
{
	return SeqCheckFlag(flgEggCarrierInTheSea[GetPlayerNumber()]);
}

// FUNCTION: SADX 0x004f5830
void EV_PcNpcInit()
{
	if (DAT_05cd0f24 != 0)
		return;
	switch (((DAT_05b9d724 << 8 | DAT_05b9d744) >> 8) & 0xff)
	{
		case 0x1a:
			SSPcInit();
			break;
		case 0x1d:
			ECPcSet();
			break;
		case 0x20:
			EC_CPcSet();
			break;
		case 0x21:
			MRPcInit();
			break;
		case 0x22:
			PASTPcInit();
			break;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x004f58c0
void EV_PcNpcEnd()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f5950
void SeqTaskFadeIn(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05ccde10 != 0)
	{
		local_8->mode = 2;
	}
	switch (local_8->mode)
	{
		case 0:
			tp->disp = DisplayFade;
			tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
			local_8->mode = 1;
			local_8->value.f = 255.0;
			break;
		case 1:
			DAT_05cd14d4 = 0;
			DisplayFade(tp);
			local_8->value.f -= 16.0;
			if (local_8->value.f < 0.0)
			{
				local_8->value.f = 0.0;
				local_8->mode = 2;
			}
			break;
		case 2:
			FreeTask(tp);
			break;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x004f5a10
void DisplayFade(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f5ac0
void SeqTaskFadeOut(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	switch (local_8->mode)
	{
		case 0:
			tp->disp = DisplayFade;
			tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
			local_8->mode = 1;
			local_8->value.f = 15.0;
		case 1:
			DisplayFade(tp);
			local_8->value.f += 16.0;
			if (local_8->value.f > 255.0)
			{
				local_8->value.f = 255.0;
				local_8->mode = 2;
				DAT_05cd14d4 = 1;
			}
			break;
		case 2:
			DisplayFade(tp);
			FreeTask(tp);
			break;
	}
}

// FUNCTION: SADX 0x004f5ee0
void SeqResetLastScenario()
{
	int local_8g;
	int local_cg;
	*(short *)(DAT_05b3ea28 + 4) = 0;
	*(short *)(DAT_05b3ea28 + 2) = 0;
	local_cg = DAT_05baf544;
	SetEntranceNumber(*(char *)(local_cg + 6));
	SetStageNumber(*(unsigned char *)(local_cg + 4), *(unsigned char *)(local_cg + 5));
	*(short *)(DAT_05b3ea28 + 10) = (short)(DAT_05b9d724 << 8 | DAT_05b9d744);
	for (local_8g = 0; last_eventlist[local_8g] != 0; local_8g++)
	{
		DAT_05baf900[last_eventlist[local_8g]] = 0;
	}
}
