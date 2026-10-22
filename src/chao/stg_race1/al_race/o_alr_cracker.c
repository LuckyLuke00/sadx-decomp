#include "decls.h"
extern int DAT_05b35c44;
extern int DAT_05b35c48;

// FUNCTION: SADX 0x00489c90
void ObjectAlrCracker_Start()
{
	DAT_05b35c48 = 1;
	DAT_05b35c44 = GetGoalProductionLevel();
}

// FUNCTION: SADX 0x00489cb0
long ObjectAlrCracker_GetFlag()
{
	return DAT_05b35c48;
}
