#include "decls.h"

// FUNCTION: SADX 0x00711950
struct task *ALK_BaseWindowCreate(struct task *ptp, const struct ALK_WINDOW_TABLE *pTable, const struct ALK_BWINDOW_TABLE *bTable)
{
	struct task *local_8;
	void *local_4;

	if (ptp == 0)
	{
		return 0;
	}
	local_8 = CreateChildTask(0, (void (__cdecl *)(struct task *))FUN_007d21b0, ptp);
	if (local_8 != 0)
	{
		local_8->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		local_4 = CAlloc(1, 0x6c);
		if (local_4 == 0)
		{
			DestroyTask(local_8);
			return 0;
		}
		*(struct ALK_WINDOW_TABLE *)local_4 = *pTable;
		local_8->awp = (struct anywk *)local_4;
		*(struct ALK_BWINDOW_TABLE *)((char *)local_4 + 0x1c) = *bTable;
		return local_8;
	}
	return 0;
}
