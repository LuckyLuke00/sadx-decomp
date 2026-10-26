#include "decls.h"
extern int DAT_060c5ac0;
extern int DAT_060c5ac4;

// FUNCTION: SADX 0x0070efd0
void E101R_InitAfterImagePartsPos(struct task *pTask)
{
	DAT_060c5ac0 = 0;
	DAT_060c5ac4 = 0;
}

// STUB: SADX 0x0070f020
void E101R_CalcAfterImageNum(struct E101R_WK *pE101RWk, int flag, int *pNum)
{
}

// STUB: SADX 0x0070f400
void E101R_SetAfterImagePos(struct task *pTask)
{
}

// STUB: SADX 0x0070fb50
void E101R_AfterImageMagni(struct E101R_WK *pE101RWk, struct NJS_ACTION *pAction)
{
}
