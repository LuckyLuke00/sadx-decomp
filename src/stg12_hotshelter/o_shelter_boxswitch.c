#include "decls.h"
extern int DAT_060dd3a0;
extern int DAT_060dd3a4;
extern int DAT_060dd3a8;
extern int DAT_060dd3ac;
extern int DAT_060dd3b0;
extern int DAT_060dd3b4;
extern int DAT_060dd3b8;
extern int DAT_060dd3bc;

// FUNCTION: SADX 0x008a2b60
void InitBoxSwitch()
{
	DAT_060dd3a0 = 0;
	DAT_060dd3a4 = 0;
	DAT_060dd3a8 = 0;
	DAT_060dd3ac = 0;
	DAT_060dd3b0 = 0;
	DAT_060dd3b4 = 0;
	DAT_060dd3b8 = 0;
	DAT_060dd3bc = 0;
}

// STUB: SADX 0x008a2b90
int GetBoxSwitchOnOff(int no)
{
	return (*(int (*)[])&DAT_060dd3a0)[no];
}
