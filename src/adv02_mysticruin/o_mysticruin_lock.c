#include "decls.h"
extern int MRLockSeqVarID[8][4];
extern unsigned char DAT_05bafb00[];

// STUB: SADX 0x006b6d10
void SetLockOpen(int Kind, int Flg)
{
}

// FUNCTION: SADX 0x006b6d80
int GetLockOpen(int Kind)
{
	int iVar1 = GetPlayerCharacterName(0);
	int iVar2 = MRLockSeqVarID[iVar1][Kind];
	if (iVar2 >= 0)
		return DAT_05bafb00[iVar2];
	return 0;
}

// STUB: SADX 0x006b71a0
void DesertTaskData(struct task *tp)
{
}
