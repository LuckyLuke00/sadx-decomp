#include "decls.h"
extern struct task *DAT_060b9540;
extern struct task *DAT_060b9560;

// FUNCTION: SADX 0x006bc300
void FUN_006bc300(void)
{
	struct task **var1 = (struct task **)&DAT_060b9540;

	do
	{
		if (*var1 != NULL)
		{
			FreeTask(*var1);
			*var1 = NULL;
		}
		var1++;
	} while ((long)var1 < (long)&DAT_060b9560);
}
