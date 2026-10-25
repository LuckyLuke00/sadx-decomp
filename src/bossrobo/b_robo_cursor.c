#include "decls.h"
extern int DAT_060bd1ac;
extern float DAT_060bd1a0;
extern float DAT_060bd1a4;
extern float DAT_060bd1a8;

// FUNCTION: SADX 0x006e1790
void RoboLockOnCursor_GetPos(struct NJS_POINT3 *pPos)
{
	pPos->x = DAT_060bd1a0;
	pPos->y = DAT_060bd1a4;
	pPos->z = DAT_060bd1a8;
}

// FUNCTION: SADX 0x006e17b0
void FUN_006e17b0()
{
	DAT_060bd1ac = 2;
}

// FUNCTION: SADX 0x006e17c0
void RoboLockOnCursor_Off()
{
	DAT_060bd1ac = 1;
}

// STUB: SADX 0x006e1a80
void RoboLockOnCursor()
{
}
