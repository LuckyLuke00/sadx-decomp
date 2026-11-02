#include "decls.h"
extern struct CUSTOM_OBJ panel_model[];
extern struct CUSTOM_OBJ DAT_05a92154;
extern int DAT_05edbe90;
void FUN_005b6f80(struct task *param_1);
extern char DAT_05edbe94[64];
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

// FUNCTION: SADX 0x005b60c0
void itembox_airDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (dsCheckViewV(&local_8->pos, 20.0f) == 0)
	{
		return;
	}
	DAT_05edbe84 = (struct NJS_MODEL *)tp->awp->work.ptr[0];
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)local_8->ang.z);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(0, (unsigned short)local_8->ang.x);
	}
	if (local_8->ang.y != 0)
	{
		njRotateY(0, (unsigned short)local_8->ang.y);
	}
	SetRegularTexture();
	if (local_8->mode == 1 || local_8->mode == 0)
	{
		FUN_0067d2d0(0, *(float *)((char *)DAT_05edbe84 + 0x1c), *(float *)((char *)DAT_05edbe84 + 0x1c), *(float *)((char *)DAT_05edbe84 + 0x1c));
		DrawCustomObject_wz((struct obj *)&DAT_05a92154, &panel_model[0]);
	}
	else
	{
		FUN_0067d2d0(0, *(float *)((char *)DAT_05edbe84 + 0x18), *(float *)((char *)DAT_05edbe84 + 0x18), *(float *)((char *)DAT_05edbe84 + 0x18));
		SaveConstantAttr();
		OnConstantAttr(0, 0x100000);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		SetMaterial(-(*(float *)((char *)DAT_05edbe84 + 0x18) - 1.0) * 0.25, 0.0, 0.0, 0.0);
		DrawCustomObject_wz((struct obj *)&DAT_05a92154, &panel_model[0]);
		ResetMaterial();
		LoadConstantAttr();
	}
	njPopMatrix(1);
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
void FUN_005b6680(int param_1)
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
	*(long *)(DAT_05edbe94 + (DAT_05edbe8c << 4) + 0) = panel;
	*(float *)(DAT_05edbe94 + (DAT_05edbe8c << 4) + 4) = -60.0f;
	*(float *)(DAT_05edbe94 + (DAT_05edbe8c << 4) + 8) = 2.0f;
	*(int *)(DAT_05edbe94 + (DAT_05edbe8c << 4) + 12) = DAT_05edbfe0;
	DAT_05edbe8c = DAT_05edbe8c + 1;
	DAT_05edbe88 = 1;
}

// STUB: SADX 0x005b67b0
void FUN_005b67b0(struct task *param_1)
{
}

// STUB: SADX 0x005b6820
void FUN_005b6820(void)
{
}

// FUNCTION: SADX 0x005b6940
void FUN_005b6940()
{
	int local_8;
	for (local_8 = 0; local_8 < DAT_05edbe8c; local_8++)
	{
		*(float *)(DAT_05edbe94 + local_8 * 0x10 + 8) += 0.20000000298023224;
		if (*(float *)(DAT_05edbe94 + local_8 * 0x10 + 8) > 2.0)
			*(float *)(DAT_05edbe94 + local_8 * 0x10 + 8) = 2.0;
	}
	DAT_05edbe90++;
	if ((unsigned)DAT_05edbe90 > 0x3c)
	{
		DAT_05edbe90 = 0x3c;
		DAT_05edbe88 = 3;
	}
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
