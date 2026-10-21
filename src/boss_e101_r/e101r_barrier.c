#include "decls.h"
extern int DAT_060c4aa8;
extern int DAT_060c4ab4;

// FUNCTION: SADX 0x0070ee70
void E101R_BarrierExit()
{
	DAT_060c4ab4 = 0;
}

// FUNCTION: SADX 0x0070ee80
void E101R_BarrierSetMode(int mode)
{
	DAT_060c4aa8 = mode;
}
