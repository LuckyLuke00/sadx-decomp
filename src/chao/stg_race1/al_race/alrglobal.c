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

// FUNCTION: SADX 0x0048f7e0
int GetHomeTownFromId(enum IAM *i_am, int id)
{
	if (DAT_05b33108 == 0)
		return 0;
	switch (DAT_05b33108->entry[id].garden)
	{
	case 0:
		*i_am = (enum IAM)0;
		break;
	case 1:
		*i_am = (enum IAM)1;
		break;
	case 2:
		*i_am = (enum IAM)2;
		break;
	case 3:
		*i_am = (enum IAM)3;
		break;
	case 4:
		*i_am = (enum IAM)4;
		break;
	default:
		return 0;
	}
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

// STUB: SADX 0x0048f8b0
int GetRacerInfoFromRank(int rank, enum Alr_Info info)
{
	return (int)0;
}

// STUB: SADX 0x0048f940
void CallFanFanSerif(int lane, enum TypeFanFan type)
{
}

// STUB: SADX 0x0048fa00
enum P_LEVEL GetGoalProductionLevel()
{
	return (enum P_LEVEL)0;
}
