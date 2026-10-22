#include "decls.h"
void FUN_00422560(int param_1);
void njSetZUpdateMode(long param_1);
void ResetMaterial();
extern unsigned char DAT_05cda0a4;

// FUNCTION: SADX 0x00598b90
void FUN_00598b90()
{
	DAT_05cda0a4 = 1;
}

// FUNCTION: SADX 0x00598ba0
void FUN_00598ba0()
{
	DAT_05cda0a4 = 0;
	FUN_00422560(3);
	njSetZUpdateMode(1);
	ResetMaterial();
}
