#include "decls.h"
extern struct task *DAT_05edbc84;
extern int DAT_05edbc88;

// FUNCTION: SADX 0x005a6360
int CloseDownload()
{
	if (DAT_05edbc88 != 0)
	{
		DestroyTask(DAT_05edbc84);
	}
	DAT_05edbc88 = 0;
	return 1;
}
