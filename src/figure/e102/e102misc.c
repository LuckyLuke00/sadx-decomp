#include "decls.h"

// STUB: SADX 0x005d2890
void E102ResetDelayAnalogKey(struct E102WK *ewk, int pno)
{
}

// FUNCTION: SADX 0x005d2910
void SetE102DashPanelAccel(int pno)
{
	char *local_8;
	local_8 = (char *)DAT_05baf368[pno];
	*local_8 = 0x2d;
}
