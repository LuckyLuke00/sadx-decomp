#include "decls.h"
extern int DAT_060cb340;

// FUNCTION: SADX 0x00718120
void FUN_00718120(int param_1, int param_2, int param_3, int param_4)
{
	void *local_8 = TH_GetWork(0);
	local_8 = (char *)local_8 + DAT_060cb340;
	dsPlay_timer(param_1, (int)local_8, 1, 0, 0x78);
	dsVolume_id((int)local_8, param_2);
	dsPan_id((int)local_8, param_3);
	dsPitch_id((int)local_8, param_4);
	DAT_060cb340 = (DAT_060cb340 + 1) & 0x1f;
}
