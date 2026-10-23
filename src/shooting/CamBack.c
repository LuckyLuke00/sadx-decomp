#include "decls.h"
extern long CamBackDelay;
extern long CamBackTarget;
extern int DAT_060ce418;
extern int DAT_060ce4a8;

// FUNCTION: SADX 0x007ec4f0
void CameraDeadSet()
{
	DAT_060ce4a8 = DAT_060ce418 - 0xa;
	CameraSetNormalCamera(0x44, 3);
}

// FUNCTION: SADX 0x007ec510
void CameraBackInit(long mode)
{
	switch (mode)
	{
		case 0:
			CamBackDelay = 10;
			CamBackTarget = 10;
			break;
		case 1:
			CamBackDelay = 10;
			CamBackTarget = 5;
			break;
	}
}

// STUB: SADX 0x007ec550
void sht_CalcTargetPos(float dist, struct NJS_POINT3 *ans)
{
}
