#include "decls.h"

// FUNCTION: SADX 0x006ac0f0
int CheckOpenState()
{
	if (GetPlayerCharacterName(0) == 0)
	{
		if (SeqCheckFlag(0xae))
		{
			return SeqCheckFlag(0xaf);
		}
	}
	{
		int var1 = SeqVarID[GetPlayerCharacterName(0)];
		if (var1 >= 0)
		{
			return *(unsigned char *)(0x5bafb00 + var1);
		}
		return 0;
	}
}
