#include "decls.h"
extern int DAT_060c4658;
extern int DAT_060c4644;
extern float DAT_060c4678;

// FUNCTION: SADX 0x0070ab50
void CamE101R_SetViewHeight(float fHeight)
{
	DAT_060c4678 = fHeight;
}

// FUNCTION: SADX 0x0070ab80
void CamE101R_SetMissileFlag(long flag)
{
	DAT_060c4644 = flag;
}

// FUNCTION: SADX 0x0070abf0
long CamE101R_GetAngle()
{
	return DAT_060c4658;
}
