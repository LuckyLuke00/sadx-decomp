#include "decls.h"
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

// STUB: SADX 0x0059dcf0
unsigned char GetEnableMiniGameNumAll()
{
	return (unsigned char)0;
}

// STUB: SADX 0x0059e0d0
int AvaGetEndingEnable(enum AvaCharEnum chnum)
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
