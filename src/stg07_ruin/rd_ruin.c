#include "decls.h"
extern signed char DAT_060d12b6;
extern short DAT_060d12b4;
extern struct taskwk *DAT_05baf368[8];
void FUN_0058b860(int param_1, int param_2);
int GetSwitchOnOff(unsigned int ID);
void SetLineringEffect(long on);
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// FUNCTION: SADX 0x0084ea40
void RuinBgmControl(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->btimer--;
	if (var1->btimer == 0)
	{
		ADXTaskInit();
		BGM_Play(var1->mode);
		DestroyTask(tp);
	}
}

// STUB: SADX 0x0084eb00
void FUN_0084eb00(struct task *param_1)
{
}

// FUNCTION: SADX 0x0084ec10
void LongLineRingExec()
{
	switch (DAT_060d12b6)
	{
		case 0:
			if (GetSwitchOnOff(2) != 0)
			{
				DAT_060d12b6 = 1;
				DAT_060d12b4 = 0;
			}
			break;
		case 1:
			if (*(float *)((char *)DAT_05baf368[0] + 0x20) < 7600.0)
			{
				FUN_0058b860(3, 1);
				SetLineringEffect(0);
				DAT_060d12b6 = 2;
			}
			else
			{
				DAT_060d12b4++;
				if (DAT_060d12b4 > 600)
				{
					DAT_060d12b4 = 0;
					SetLineringEffect(1);
					FUN_0058b860(3, 0);
					DAT_060d12b6 = 0;
				}
			}
			break;
		case 2:
			DAT_060d12b4++;
			if (DAT_060d12b4 > 600)
			{
				DAT_060d12b4 = 0;
				SetLineringEffect(1);
				DAT_060d12b6 = 0;
			}
			FUN_0058b860(3, 0);
			break;
	}
}

// STUB: SADX 0x0084edb0
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x0084ee80
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x0084f5c0
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0084f640
void Bg_Ruin(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
