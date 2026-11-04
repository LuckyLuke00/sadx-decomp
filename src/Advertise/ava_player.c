#include "decls.h"

// FUNCTION: SADX 0x0061e6e0
enum AvaCharEnum GetSelectEnableChars()
{
	if (DAT_05cd14ea == 2)
	{
		return AVA_SUPERSONIC;
	}
	if (DAT_05cd14e0 != 0)
	{
		return AVA_CHAR_MAX;
	}
	if (DAT_05cd14ea == 1)
	{
		if (AvaCheckMetalSonic() != 0)
		{
			return AVA_CHAR_MAX;
		}
		else
		{
			return AVA_SUPERSONIC;
		}
	}
	else
	{
		if (SeqCheckFlag(0x47) != 0)
		{
			return AVA_CHAR_MAX;
		}
		else
		{
			return AVA_SUPERSONIC;
		}
	}
}
