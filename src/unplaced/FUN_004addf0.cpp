#include "decls.h"

extern int DAT_05b3e058;
extern int DAT_05b3e060;
extern int DAT_05b3e924;
extern int DAT_05b3ea00;
extern int DAT_05b3ea04;
extern int DAT_05b3e46c[20][14];

bool FUN_004ab0b0();
void FUN_007d21b0(void *param_1);
void FUN_004ade40();

// FUNCTION: SADX 0x004addf0
void FUN_004addf0()
{
	DAT_05b3e060 = 0;
	DAT_05b3e058 = DAT_05b3e060;
	InitSystemTV();
	FUN_007d21b0(0);
	dsInitInt(1, 1);
	FUN_004ade40();
	Reset();
	input_reset();
}

// FUNCTION: SADX 0x004ade40
void FUN_004ade40()
{
	int i;

	DAT_05b3ea00 = 0;
	DAT_05b3ea04 = 0;
	FUN_004ab0b0();
	DAT_05b3e924 = 0;
	for (i = 0; i < 20; i++)
	{
		DAT_05b3e46c[i][0] = 0;
	}
	InitOverlapSE(1);
}
