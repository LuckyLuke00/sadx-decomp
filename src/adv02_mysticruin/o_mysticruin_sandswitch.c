#include "decls.h"
extern unsigned char DAT_05bafb00[];

// FUNCTION: SADX 0x006b9680
int GetSandSwitchOnOff()
{
	int iVar1 = GetPlayerCharacterName(0);
	int iVar2 = MRSandSwitchSeqVarID[iVar1];
	if (iVar2 >= 0)
		return DAT_05bafb00[iVar2];
	return 0;
}
