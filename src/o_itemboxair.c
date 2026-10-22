#include "decls.h"
void FUN_005b69e0();
void FUN_005b6f80(struct task *param_1);
extern int DAT_05edbfe0;
extern int DAT_05edbe88;
extern int DAT_05edbe8c;
extern float DAT_05edbe80;
void FUN_005b67b0(struct task *param_1);
extern struct NJS_MODEL *DAT_05edbe84;

// STUB: SADX 0x005b5df0
void PutItem_ItemBoxAir(struct NJS_POINT3 *putpos, long putItem)
{
}

// STUB: SADX 0x005b6290
void *FUN_005b6290()
{
	return (void *)0;
}

// STUB: SADX 0x005b62e0
void sphereDraw(struct obj *obj)
{
}

// FUNCTION: SADX 0x005b6680
void FUN_005b6680(void)
{
	*(int *)((char *)DAT_05edbe84 + 0x14) += 0x222;
}

// FUNCTION: SADX 0x005b66a0
void FUN_005b66a0(int param_1)
{
	DAT_05edbe84->center.x = DAT_05edbe84->center.x + 0.20000000298023224;
	if (DAT_05edbe84->center.x >= 5.0)
	{
		DAT_05edbe84->center.x = 5.0f;
		*(char *)(*(int *)(param_1 + 0x20)) = 4;
	}
}

// FUNCTION: SADX 0x005b66f0
void InitItemBoxManager()
{
	struct task *local_8;

	local_8 = CreateElementalTask(2, 3, FUN_005b67b0);
	local_8->disp = itemBoxManager;
	local_8->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
	DAT_05edbe8c = 0;
	DAT_05edbe88 = 0;
	DAT_05edbe80 = -1.0f;
}

// FUNCTION: SADX 0x005b6740
void EntryItemBoxPanel(long panel)
{
	*(long *)(0x5edbe94 + DAT_05edbe8c * 0x10) = panel;
	*(float *)(0x5edbe98 + DAT_05edbe8c * 0x10) = -60.0f;
	*(float *)(0x5edbe9c + DAT_05edbe8c * 0x10) = 2.0f;
	*(int *)(0x5edbea0 + DAT_05edbe8c * 0x10) = DAT_05edbfe0;
	DAT_05edbe8c = DAT_05edbe8c + 1;
	DAT_05edbe88 = 1;
}

// STUB: SADX 0x005b67b0
void FUN_005b67b0(struct task *tp)
{
}

// STUB: SADX 0x005b69e0
void FUN_005b69e0()
{
}

// STUB: SADX 0x005b6f50
void ItemBox_Explosion(struct NJS_POINT3 *pos)
{
}

// STUB: SADX 0x005b6f80
void FUN_005b6f80(struct task *param_1)
{
}

// STUB: SADX 0x005b7060
void itemDisp_itembox(struct task *tp)
{
}
