#include "decls.h"
extern void *DAT_05b39bb4;
extern void *DAT_05b42898;
extern void *DAT_05b4296c;

// FUNCTION: SADX 0x0049a580
void ReleaseMissionCamera()
{
	if (DAT_05b39bb4)
	{
		syFree(DAT_05b39bb4);
		DAT_05b39bb4 = 0;
	}
	DAT_05b4296c = 0;
	DAT_05b42898 = 0;
}
