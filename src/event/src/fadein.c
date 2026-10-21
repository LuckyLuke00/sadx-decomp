#include "decls.h"
extern struct task *DAT_060ccd78;

// FUNCTION: SADX 0x007dda80
void fadein_delete()
{
	if (DAT_060ccd78)
	{
		FreeTask(DAT_060ccd78);
		DAT_060ccd78 = 0;
	}
}
