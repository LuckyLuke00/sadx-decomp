#include "decls.h"

// STUB: SADX 0x007116d0
void ALK_ChangeMaterial(unsigned long color)
{
}

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

#pragma optimize("", off)
// STUB: SADX 0x007119c0
void ALK_SelectWindowExec(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x00711a90
void ALK_SelectWindowDraw(struct task *tp)
{
}

// STUB: SADX 0x00711b70
struct task *ALK_SelectWindowCreate(struct task *ptp, long id, const struct ALK_WINDOW_TABLE *pTable, const struct ALK_SWINDOW_TABLE *sTable)
{
	return (struct task *)0;
}
