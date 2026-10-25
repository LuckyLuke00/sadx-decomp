#include "decls.h"
extern struct task *DAT_060ccb80;
extern void *DAT_060ccb78;
extern void *DAT_060ccb7c;

// STUB: SADX 0x007dcb80
void SetCloudScroll(struct cloud_scroll *scroll)
{
}

// FUNCTION: SADX 0x007dd000
void CEcCloud_Stop()
{
	if (DAT_060ccb80 != 0)
	{
		FreeTask(DAT_060ccb80);
		DAT_060ccb80 = 0;
		Free(DAT_060ccb78);
		Free(DAT_060ccb7c);
	}
}

// FUNCTION: SADX 0x007dd190
void CEcCloud_Start(float scale, int num)
{
	if (DAT_060ccb80 == 0)
	{
		DAT_060ccb80 = CreateElementalTask(2, 5, EggCarrierCloud);
		base_scale = scale;
		main_cloudnum = num;
		DAT_060ccb78 = MAlloc(num * 0x2c);
		main_cloud.tbl = (struct cloudtbl *)DAT_060ccb78;
		main_cloud.numtbl = main_cloudnum;
		DAT_060ccb7c = MAlloc(main_cloudnum * 0x2c);
		main_cloud2.tbl = (struct cloudtbl *)DAT_060ccb7c;
		main_cloud2.numtbl = main_cloudnum;
	}
}
