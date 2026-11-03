#include "decls.h"

extern int DAT_05b3e058;
extern int DAT_05b3e060;

void FUN_007d21b0(...);
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

