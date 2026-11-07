#include "decls.h"
extern int DAT_060dd3a0[8];

// FUNCTION: SADX 0x008a2b60
void InitBoxSwitch()
{
	DAT_060dd3a0[0] = 0;
	DAT_060dd3a0[1] = 0;
	DAT_060dd3a0[2] = 0;
	DAT_060dd3a0[3] = 0;
	DAT_060dd3a0[4] = 0;
	DAT_060dd3a0[5] = 0;
	DAT_060dd3a0[6] = 0;
	DAT_060dd3a0[7] = 0;
}

// FUNCTION: SADX 0x008a2b90
int GetBoxSwitchOnOff(int no)
{
	return DAT_060dd3a0[no];
}
