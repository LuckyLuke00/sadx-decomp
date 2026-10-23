#include "decls.h"
extern int DAT_060bd560;
extern int DAT_060bd538;
extern int DAT_060bd53c;
extern int DAT_060bd540;
extern int DAT_060bd544;
extern int DAT_060bd548;
extern int DAT_060bd54c;
extern int DAT_060bd550;
extern int DAT_060bd554;
extern int DAT_060bd558;
extern int DAT_060bd55c;
extern void *DAT_06276c40;

// FUNCTION: SADX 0x006e2dc0
void FUN_006e2dc0()
{
	int *var1;

	if (!(DAT_060bd560 & 1))
	{
		DAT_060bd560 |= 1;
		var1 = (int *)DAT_06276c40;
		DAT_060bd538 = var1[0x24];
		DAT_060bd53c = var1[0x17];
		DAT_060bd540 = var1[0x19];
		DAT_060bd544 = var1[0x23];
		DAT_060bd548 = var1[0xb];
		DAT_060bd54c = var1[0xd];
		DAT_060bd550 = var1[3];
		DAT_060bd554 = var1[1];
		DAT_060bd558 = var1[2];
		DAT_060bd55c = 0;
	}
	clrObjFlags((struct obj **)&DAT_060bd538, 4);
}
