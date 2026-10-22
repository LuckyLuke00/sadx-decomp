#include "decls.h"
extern int DAT_05ccdbd0;

// FUNCTION: SADX 0x008014a0
int FUN_008014a0()
{
	if (IsCompulsionCamera() == 0)
	{
		if (IsEventCamera() != 0)
		{
			CameraReleaseEventCamera();
		}
	}
	DAT_05ccdbd0 = 0;
	return 1;
}
