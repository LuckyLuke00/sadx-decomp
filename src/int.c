#include "decls.h"
extern int DAT_05b9d844;
extern int DAT_05b9d834;
extern int DAT_05b9d838;
extern int DAT_05a922f4;

// FUNCTION: SADX 0x004cb7d0
void dsInitInt(int vsync, int loop)
{

	DAT_05b9d844 = vsync;
	DAT_05b9d834 = loop;
	DAT_05b9d838 = 0;
	switch (vsync)
	{
	case 1:
		njSetWaitVsyncCount(DAT_05a922f4);
		break;
	case 2:
		if (DAT_05a922f4 == 1)
		{
			njSetWaitVsyncCount(2);
		}
		break;
	}
	njSetVSyncFunction(dsVSyncServer);
}

// STUB: SADX 0x004cb9b0
void dsVSyncServer()
{
}
