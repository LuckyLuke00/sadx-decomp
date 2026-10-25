#include "decls.h"
extern struct NJS_ARGB DAT_05b3e040;
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT3 DAT_05b3e074;
extern struct NJS_POINT2 DAT_05b3e080;
extern int DAT_05b3e0d0;
extern short DAT_05b9d744;
extern struct NJS_ARGB *pFogTable_Stg08[];
extern struct NJS_POINT2 *pClipSky_Stg08[];
extern struct NJS_POINT2 *pClipMap_Stg08[];
extern struct NJS_POINT3 *pScale_Stg08[];
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

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
