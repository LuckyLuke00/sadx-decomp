#include "decls.h"
struct taskwk;
struct NJS_ACTION;

// STUB: SADX 0x006ba230
void SetMonkeyAction(struct taskwk *twp, int ActNo)
{
}

// FUNCTION: SADX 0x006ba5b0
void SetMonkeyCageBomb(int Kind, int Flg)
{
	int iVar1 = GetPlayerCharacterName(0);
	int iVar2 = SeqVarID[iVar1][Kind];
	if (iVar2 >= 0)
		DAT_05bafb00[iVar2] = (unsigned char)Flg;
}

// FUNCTION: SADX 0x006ba5e0
int GetMonkeyCageBomb(int Kind)
{
	int iVar1 = GetPlayerCharacterName(0);
	int iVar2 = SeqVarID[iVar1][Kind];
	if (iVar2 >= 0)
		return DAT_05bafb00[iVar2];
	return 0;
}
