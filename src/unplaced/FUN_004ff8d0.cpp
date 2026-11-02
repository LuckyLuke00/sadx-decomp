#include "decls.h"
extern char DAT_05cbef80[121];

// FUNCTION: SADX 0x004ff8d0
int FUN_004ff8d0(void)
{
	int local_8 = -1;
	if ((int)DAT_05cbeffb > 0)
	{
		DAT_05cbeffb--;
		local_8 = (int)(signed char)DAT_05cbef80[DAT_05cbeffb * 0xc];
	}
	return local_8;
}
