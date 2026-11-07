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

// FUNCTION: SADX 0x007119c0
void ALK_SelectWindowExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	if ((var1->flag & 1) == 0)
	{
		if ((var2->work.ub[0x18] & 1) != 0 && var1->id == *(char *)(var2->work.ptr[8]))
		{
			var1->scl.y = 0.1f;
			var1->flag |= 1;
			return;
		}
	}
	else
	{
		if (var1->scl.y > 0.0f)
		{
			var1->ang.x += 0x2000;
			var1->scl.x = njSin(var1->ang.x) * var1->scl.y + 1.0f;
			var1->scl.y *= 0.8999999761581421;
			if (var1->scl.y < 0.01f)
			{
				var1->ang.x = 0;
				var1->scl.y = 0.0f;
				var1->scl.x = 1.0f;
			}
		}
		if ((var2->work.ub[0x18] & 1) != 0 && var1->id != *(char *)(var2->work.ptr[8]))
		{
			var1->flag &= 0xfffe;
			var1->scl.x = 1.0f;
			var1->ang.x = 0;
		}
	}
}

// STUB: SADX 0x00711a90
void ALK_SelectWindowDraw(struct task *tp)
{
}

// STUB: SADX 0x00711b70
struct task *ALK_SelectWindowCreate(struct task *ptp, long id, const struct ALK_WINDOW_TABLE *pTable, const struct ALK_SWINDOW_TABLE *sTable)
{
	return (struct task *)0;
}
