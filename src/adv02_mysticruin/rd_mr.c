#include "decls.h"
extern struct task *DAT_060b8840[9];
void FUN_006a8690(struct task *param_1);
extern struct NJS_TEXLIST texlist_mapMR;
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2);

// STUB: SADX 0x006a80e0
void FUN_006a80e0(void)
{
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

// STUB: SADX 0x006a8140
void task_set_icestone(struct task *tp)
{
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

// STUB: SADX 0x006a8440
void FUN_006a8440()
{
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
void FUN_006a8690(struct task *pt)
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
