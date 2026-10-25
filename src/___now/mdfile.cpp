#include "decls.h"
void FUN_004cb070(void *param_1);

// FUNCTION: SADX 0x0059d430
void MDHeaderClose(struct MDHANDLE *mdh)
{
	int local_8g;
	if (mdh == 0)
	{
		return;
	}
	if (*(void **)((char *)mdh + 0x14))
	{
		FUN_004cb070(*(void **)((char *)mdh + 0x14));
	}
	else
	{
		for (local_8g = 0; local_8g < *(int *)((char *)mdh + 0x18); local_8g++)
		{
			FUN_004cb070(*(void **)((char *)mdh + local_8g * 0xc + 0x1c));
		}
	}
	if (mdh)
	{
		FUN_004cb070(*(void **)((char *)mdh + 0x10));
		FUN_004cb070(mdh);
	}
}
