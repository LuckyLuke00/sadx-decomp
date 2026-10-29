#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_POINT3 DAT_026f0878;
extern union NJS_COLOR DAT_026f0888;
static void SetTableBg();
extern struct task *DAT_060b8840[9];
void FUN_006a8690(struct task *param_1);
extern struct NJS_TEXLIST texlist_mapMR;
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2);

#pragma optimize("", off)
// STUB: SADX 0x006a7d60
static void SetTableBg()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006a80e0
void FUN_006a80e0(void)
{
	int var1;

	for (var1 = 0; var1 < 8; var1++)
	{
		if (DAT_060b8840[var1] != 0)
		{
			DestroyTask(DAT_060b8840[var1]);
			DAT_060b8840[var1] = 0;
		}
	}
}

// FUNCTION: SADX 0x006a8110
void RdExit(struct task *tp)
{
	int var1;

	for (var1 = 0; var1 < 8; var1++)
	{
		if (DAT_060b8840[var1] != 0)
		{
			DestroyTask(DAT_060b8840[var1]);
			DAT_060b8840[var1] = 0;
		}
	}
	___njFogDisable();
}

// FUNCTION: SADX 0x006a8140
void task_set_icestone(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->wtimer == 0)
	{
		struct task *var2 = CreateElementalTask(3, 3, ObjectMysticRuinHandyKey);
		var2->twp->scl.x = 0.0f;
		HoldTaskP(0, var2);
		FreeTask(tp);
	}
	else
	{
		var1->wtimer--;
	}
}

// STUB: SADX 0x006a8190
void FUN_006a8190(void)
{
}

// STUB: SADX 0x006a8200
void act3_river_exit(struct task *tp)
{
}

// STUB: SADX 0x006a8250
void act3_river_scroll(struct task *tp)
{
}

// STUB: SADX 0x006a82d0
void AnimTexture(struct task *tp)
{
}

// FUNCTION: SADX 0x006a8440
void FUN_006a8440()
{
	struct NJS_POINT3COL local_14;

	if (DAT_05b9d838 == 0)
	{
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		local_14.num = 4;
		local_14.p = (struct NJS_POINT3 *)&DAT_026f0888;
		local_14.col = (union NJS_COLOR *)&DAT_026f0878;
		local_14.tex = 0;
		___njDrawPolygon3D(&local_14, 4, 0x20);
	}
}

// FUNCTION: SADX 0x006a84a0
long LoadMapMR(unsigned short act)
{
	switch (act)
	{
	case 2:
		texLoadTexturePvmFile("map_mr_j", &texlist_mapMR);
		break;
	case 1:
		texLoadTexturePvmFile("map_mr_a", &texlist_mapMR);
		break;
	case 0:
		texLoadTexturePvmFile("map_mr_s", &texlist_mapMR);
		break;
	default:
		return 0;
	}
	FUN_004b6460(&texlist_mapMR, "mapMR");
	return 1;
}

// FUNCTION: SADX 0x006a8660
void DestroyMapMR(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapMR);
	late_ReleaseTexture(&texlist_mapMR);
}

// FUNCTION: SADX 0x006a8680
void FUN_006a8680(void *param_1)
{
	SetTableBg();
}

// STUB: SADX 0x006a8690
void FUN_006a8690(struct task *param_1)
{
}

// STUB: SADX 0x006a9080
void AnimAct1Pond(struct task *tp)
{
}

// STUB: SADX 0x006a90b0
void AnimAct2Pond(struct task *tp)
{
}

// STUB: SADX 0x006a9300
void Bg_MysticRuin(struct task *tp)
{
}
