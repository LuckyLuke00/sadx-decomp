#include "decls.h"
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// STUB: SADX 0x0085a790
void sn_gdcontrol(struct task *tp)
{
}

// STUB: SADX 0x0085a9b0
void FUN_0085a9b0(void)
{
}

// FUNCTION: SADX 0x0085a9f0
void RdSnowSwitchNadareStartDestructor(struct task *tp)
{
	ObjectNadareStart();
}

// FUNCTION: SADX 0x0085aa00
void RdSnowSwitchNadareStart(struct task *tp)
{
	tp->dest = RdSnowSwitchNadareStartDestructor;
	FreeTask(tp);
}

// STUB: SADX 0x0085ac30
void RdSnowBoardingSpeedManager(struct task *tp)
{
}

// FUNCTION: SADX 0x0085ae40
void SetPlayerSnowBoard(struct task *tp)
{
	SetInputP(0, 0x2c);
	if (GetPlayerNumber() == 0)
	{
		CreateElementalTask(3, 2, SonicSnowBoard);
	}
	if (GetPlayerNumber() == 2)
	{
		CreateElementalTask(3, 2, MilesSnowBoard);
	}
	FreeTask(tp);
}

// STUB: SADX 0x0085af40
static void DestructBg(struct task *tp)
{
}

// STUB: SADX 0x0085b150
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x0085bae0
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x0085bb60
void Bg_Snow(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
