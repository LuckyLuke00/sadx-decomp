#include "decls.h"
extern int DAT_05b9d84c;
extern int DAT_05b9d848;
extern void *DAT_05b42528;
extern void *DAT_05cc3564;
extern unsigned char DAT_05cc3560;
extern unsigned char DAT_05cc3568;
extern int DAT_05cc356c;
extern unsigned char DAT_05cc3570;
void FUN_00503160();

// FUNCTION: SADX 0x005030d0
int FUN_005030d0()
{
	return 0xf;
}

// FUNCTION: SADX 0x005030e0
int FUN_005030e0()
{
	return 1;
}

// FUNCTION: SADX 0x005030f0
void InitGCMemocaState()
{
	DAT_05cc3560 = 1;
	DAT_05cc3568 = 0;
	DAT_05cc356c = 0;
	DAT_05cc3570 = 0;
	DAT_05cc3564 = NULL;
}

// FUNCTION: SADX 0x00503120
void l_edit_Init()
{
	DAT_05b9d84c = 0;
	DAT_05b9d848 = 0;
	if (DAT_05b42528 != 0)
	{
		ReleaseLineList();
	}
}

// FUNCTION: SADX 0x00503150
void SaveMissionData()
{
	FUN_00503160();
}
