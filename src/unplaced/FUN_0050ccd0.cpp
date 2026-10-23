#include "decls.h"

// FUNCTION: SADX 0x0050ccd0
void FUN_0050ccd0()
{
	if (DAT_05cd296c & 0x400)
	{
		if ((((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x300) ||
			(((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x800))
		{
		}
		else
		{
			if (((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x1200)
			{
				GM_SECall(0x57d);
			}
			else
			{
				GM_SECall(0x57a);
			}
		}
	}
	else
	{
		dsPlay_oneshot(0x585, 0, 0, 0);
	}
}
