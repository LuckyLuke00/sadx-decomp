#include "decls.h"
extern int BgmRound;
extern int BgmBackup;
extern unsigned char DAT_05bb00bc;
extern int ADX_SERIF_FLAG;
extern int SerifNo;
extern int ADX_BGM_FLAG;
extern int BgmNo;
extern int BgmLast;
extern int DAT_05bb00b4;
extern int DAT_05bb00b8;
extern struct task *DAT_05bb00c0;

// FUNCTION: SADX 0x004f5f90
void ADX_Init()
{
	wmainit();
}

// FUNCTION: SADX 0x004f5fa0
void ADX_TaskInit(struct task *tp)
{
	if (DAT_05bb00c0 == 0)
	{
		DAT_05bb00c0 = tp;
		tp->dest = ADX_free;
		tp->exec = ADX_TaskLoop;
	}
	else
	{
		DestroyTask(tp);
	}
}

// FUNCTION: SADX 0x004f62c0
void ADX_free(struct task *tp)
{
	wmastop(0);
	wmastop(1);
	BgmNo = -1;
	DAT_05bb00b8 = 0;
	BgmLast = -1;
	SerifNo = -1;
	DAT_05bb00b4 = 0;
	DAT_05bb00c0 = NULL;
}

// FUNCTION: SADX 0x004f6320
void ADX_Close()
{
	if (DAT_05bb00c0 != 0)
	{
		DestroyTask(DAT_05bb00c0);
		DAT_05bb00c0 = 0;
	}
}

// FUNCTION: SADX 0x004f6350
void BGM_Play(int no)
{
	if (ADX_BGM_FLAG != 0)
	{
		BgmNo = no;
		BgmLast = no;
	}
}

// FUNCTION: SADX 0x004f6370
void BGM_Stop()
{
	wmastop(0);
	BgmLast = 0xffffffff;
}

// FUNCTION: SADX 0x004f6390
int BGM_Status()
{
	return DAT_05bb00b8;
}

// FUNCTION: SADX 0x004f63a0
int BGM_Replay()
{
	if (BgmLast != -1)
	{
		BGM_Play(BgmLast);
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x004f63d0
void Serif_Play(int no)
{
	if (ADX_SERIF_FLAG != 0)
	{
		SerifNo = no;
	}
}

// FUNCTION: SADX 0x004f63f0
void Serif_Stop()
{
	wmastop(1);
}

// FUNCTION: SADX 0x004f6410
void Jingle_Play(int no)
{
	struct task *local_8;

	if (ADX_BGM_FLAG)
	{
		BgmNo = no;
		if (DAT_05bb00c0)
		{
			local_8 = CreateChildTask(2, JingleTask, DAT_05bb00c0);
			local_8->twp->value.l = no;
			*(int *)((char *)local_8->twp + 8) = BgmLast;
			DAT_05bb00bc = 1;
		}
	}
}

// FUNCTION: SADX 0x004f6470
void JingleDead(struct task *tp)
{
	DAT_05bb00bc = 0;
}

// FUNCTION: SADX 0x004f6530
void BGM_RequestClear()
{
	BgmNo = -1;
	DAT_05bb00b8 = 0;
	BgmLast = -1;
	BgmBackup = -1;
}

// FUNCTION: SADX 0x004f6560
void Serif_RequestClear()
{
	SerifNo = 0xffffffff;
	DAT_05bb00b4 = 0;
}

// FUNCTION: SADX 0x004f6580
struct task *ADXTaskInit()
{
	struct task *local_8;

	BGM_RequestClear();
	Serif_RequestClear();
	local_8 = CreateElementalTask(0, 1, ADX_TaskInit);
	return local_8;
}

// FUNCTION: SADX 0x004f65b0
void RoundBGM_Play(int no)
{
	if (BgmNo == no)
		return;
	if (0 != ADX_BGM_FLAG)
	{
		BgmNo = no;
		BgmRound = no;
		BgmLast = no;
	}
}
