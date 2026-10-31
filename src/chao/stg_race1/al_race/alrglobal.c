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

// FUNCTION: SADX 0x0048f790
enum Voice_Mode GetVoiceMode()
{
	if (DAT_05b33108 == 0)
		return (enum Voice_Mode)0;
	switch (*(unsigned char *)((char *)DAT_05b33108 + 0x1460))
	{
	case 3:
	case 4:
	case 9:
	case 10:
		return (enum Voice_Mode)1;
	default:
		return (enum Voice_Mode)2;
	}
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

#pragma optimize("", off)
// STUB: SADX 0x0048f880
int __fastcall FUN_0048f880(int param_1)
{
	return (int)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0048f8b0
int GetRacerInfoFromRank(int rank, enum Alr_Info info)
{
	int var1 = FUN_0048f880(rank);
	if (var1 == 0)
		return -1;
	switch (info)
	{
	case 0:
		return *(unsigned char *)(var1 + 0xc4);
	case 1:
		return (int)(long)(double)(float)(*(float *)(var1 + 0xd0));
	case 2:
		return *(unsigned short *)(*(int *)(*(int *)(var1 + 0xec) + 0xec) + 0x10);
	case 3:
		return *(unsigned short *)(*(int *)(*(int *)(var1 + 0xec) + 0xec) + 0xc);
	case 4:
		return *(unsigned short *)(*(int *)(*(int *)(var1 + 0xec) + 0xec) + 0xe);
	case 5:
		return *(unsigned short *)(*(int *)(*(int *)(var1 + 0xec) + 0xec) + 0x12);
	default:
		return -1;
	}
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
