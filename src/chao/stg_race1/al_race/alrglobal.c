#include "decls.h"
extern struct AlrReal *DAT_05b33108;

// FUNCTION: SADX 0x0048f770
int GetIdLookChao(int *look)
{
	if (DAT_05b33108 == 0)
		return 0;
	*look = DAT_05b33108->look;
	return 1;
}

// STUB: SADX 0x0048f870
int GetAlrRealDebugMode()
{
	return (int)0;
}

// STUB: SADX 0x0048f880
int __fastcall FUN_0048f880(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0048fa00
enum P_LEVEL GetGoalProductionLevel()
{
	return (enum P_LEVEL)0;
}
