#include "decls.h"
extern int DAT_060dfea8;
extern int DAT_060cd164;

// FUNCTION: SADX 0x007e44c0
void EndCartScore()
{
	DAT_060cd164 = 1;
}

// FUNCTION: SADX 0x007e4ac0
void InitCartGoal()
{
	CameraSetCollisionCameraFunc((void (__cdecl *)(_OBJ_CAMERAPARAM *))FUN_005b5aa0, 0, 0);
	DAT_060dfea8 = 1;
	CreateElementalTask(2, 3, endCheckSeq);
}
