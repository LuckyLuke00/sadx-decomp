#include "decls.h"
void FUN_005b6820();
void FUN_005b6f80(struct task *param_1);
void itemBoxManager(struct task *tp);
void FUN_005b6940();
void FUN_005b6f80(struct task *param_1);
extern float DAT_05edbfd4;
extern float DAT_05edbfd8;
extern float DAT_05edbfdc;
void FUN_005b69e0();
void FUN_005b6f80(struct task *param_1);
extern int DAT_05edbfe0;
extern int DAT_05edbe88;
extern int DAT_05edbe8c;
extern float DAT_05edbe80;
void FUN_005b67b0(struct task *param_1);
extern struct NJS_MODEL *DAT_05edbe84;

// FUNCTION: SADX 0x005b5df0
void PutItem_ItemBoxAir(struct NJS_POINT3 *putpos, long putItem)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	local_cg = CreateElementalTask(0xf, 3, ObjectItemboxAir);
	local_8g = local_cg->twp;
	local_8g->pos = *putpos;
	local_8g->scl.x = (float)putItem;
}

// STUB: SADX 0x005b60c0
void itembox_airDisplay(struct task *tp)
{
}

// STUB: SADX 0x005b6290
void *FUN_005b6290()
{
	return (void *)0;
}

// FUNCTION: SADX 0x005b62e0
void sphereDraw(struct obj *obj)
{
	struct NJS_ARGB argb;

	SaveControl3D();
	njControl3D(0x20);
	argb.b = -(DAT_05edbe84->center.x - 1.0) * 0.25;
	argb.g = argb.b;
	argb.r = argb.g;
	___njSetConstantMaterial(&argb);
	late_DrawObject(obj, 4);
	LoadControl3D();
}

// STUB: SADX 0x005b6360
void itemDraw(struct obj *obj)
{
}

// STUB: SADX 0x005b64a0
void itembox_airCollisitonBefore(struct task *tp)
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

// STUB: SADX 0x005b6820
void FUN_005b6820(void)
{
}

// STUB: SADX 0x005b6940
void FUN_005b6940()
{
}

// STUB: SADX 0x005b69e0
void FUN_005b69e0()
{
}

// STUB: SADX 0x005b6a60
void itemBoxManager(struct task *tp)
{
}

// STUB: SADX 0x005b6f50
void ItemBox_Explosion(struct NJS_POINT3 *pos)
{
}

// FUNCTION: SADX 0x005b6f80
void FUN_005b6f80(struct task *param_1)
{
	if (DAT_05edbe80 >= 0.0f)
	{
		DAT_05edbe80 = DAT_05edbe80 + 10.0;
		if (DAT_05edbe80 > 500.0)
		{
			DAT_05edbe80 = -1.0f;
		}
	}
}

// FUNCTION: SADX 0x005b6fd0
long CheckItemExplosion(struct NJS_POINT3 *pos)
{
	struct NJS_POINT3 _vec;
	if (DAT_05edbe80 >= 0.0)
	{
		_vec.x = pos->x - DAT_05edbfd4;
		_vec.y = pos->y - DAT_05edbfd8;
		_vec.z = pos->z - DAT_05edbfdc;
		if (njScalor(&_vec) < DAT_05edbe80)
			return 1;
	}
	return 0;
}

// STUB: SADX 0x005b7060
void itemDisp_itembox(struct task *tp)
{
}
