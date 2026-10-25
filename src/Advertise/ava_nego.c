#include "decls.h"
extern int DAT_00990ecc[7];
extern unsigned char DAT_05cd14ea;
int AvaCheckMetalSonic();
extern unsigned char DAT_05cd14e0;
extern int DAT_05cc3574;
extern char DAT_05cc3631;
void CreateSaveData();
int AvaGetEndingEnable(enum AvaCharEnum chnum);
unsigned char FUN_0059db20(int param_1);
extern unsigned char DAT_05cda190;
extern unsigned char DAT_05cda191;

// FUNCTION: SADX 0x0059db00
void InitAvaCmnPrm()
{
	DAT_05cda190 = 0;
	DAT_05cda191 = 0;
}

// STUB: SADX 0x0059db20
unsigned char FUN_0059db20(int param_1)
{
	return (unsigned char)0;
}

// STUB: SADX 0x0059dc20
char FUN_0059dc20(int param_1)
{
	return (char)0;
}

// FUNCTION: SADX 0x0059dca0
unsigned char GetEnableTrialActNumAll()
{
	unsigned char local_9 = 0;
	int local_8g;
	for (local_8g = 0; local_8g < 6; local_8g++)
	{
		local_9 += FUN_0059db20(local_8g);
	}
	return local_9;
}

// FUNCTION: SADX 0x0059dcf0
unsigned char GetEnableMiniGameNumAll()
{
	unsigned char local_9 = 0;
	int local_8g;
	for (local_8g = 0; local_8g < 6; local_8g++)
	{
		local_9 += (unsigned char)FUN_0059dc20(local_8g);
	}
	return local_9;
}

// STUB: SADX 0x0059dd40
void GetTrialActNowAvaStgActPrm(struct AvaStgActPrmT *stgactprmptr)
{
}

// STUB: SADX 0x0059deb0
void GetMiniGameNowAvaStgActPrm(struct AvaStgActPrmT *stgactprmptr)
{
}

// FUNCTION: SADX 0x0059df60
long GetEachCharEnable(enum AvaCharEnum chnum)
{
	long rt;
	if (DAT_05cd14e0)
	{
		return 1;
	}
	switch (chnum)
	{
		case AVA_SONIC:
			rt = SeqCheckFlag(0x41);
			break;
		case AVA_MILES:
			rt = SeqCheckFlag(0x42);
			break;
		case AVA_KNUCKLES:
			rt = SeqCheckFlag(0x43);
			break;
		case AVA_AMY:
			rt = SeqCheckFlag(0x44);
			break;
		case AVA_BIG:
			rt = SeqCheckFlag(0x46);
			break;
		case AVA_E_102:
			rt = SeqCheckFlag(0x45);
			break;
		case AVA_METALSONIC:
			if (DAT_05cd14ea == 1)
			{
				rt = AvaCheckMetalSonic();
			}
			else
			{
				rt = SeqCheckFlag(0x47);
			}
			break;
	}
	return rt;
}

// STUB: SADX 0x0059e040
char FUN_0059e040(int param_1)
{
	return (char)0;
}

// FUNCTION: SADX 0x0059e0d0
int AvaGetEndingEnable(enum AvaCharEnum chnum)
{
	if (DAT_05cd14e0 != 0)
	{
		return 1;
	}
	if (SeqCheckFlag(DAT_00990ecc[chnum]) != 0)
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x0059e110
int AvaGetTrialEnable()
{
	return (int)0;
}

// STUB: SADX 0x0059e1a0
int AvaGetMissionEnable()
{
	return (int)0;
}

// STUB: SADX 0x0059e1f0
int AvaGetPutiEnable()
{
	return (int)0;
}

// STUB: SADX 0x0059e2a0
void SetGblPlayerAndStage()
{
}

// FUNCTION: SADX 0x0059e3d0
void AvaInitFiles()
{
	SeqInit();
	CreateInitData();
}

// FUNCTION: SADX 0x0059e3e0
int AvaSaveFiles()
{
	if (DAT_05cc3574 == 0)
	{
		DAT_05cc3631 = 1;
	}
	else
	{
		CreateSaveData();
	}
	return 0;
}

// FUNCTION: SADX 0x0059e400
int AvaLoadFiles()
{
	return dsVMSLoadGame();
}

// FUNCTION: SADX 0x0059e410
int AvaCheckFiles()
{
	return FUN_005030d0();
}

// FUNCTION: SADX 0x0059e420
void AvaExtractFile()
{
	ExtractLoadData();
}
