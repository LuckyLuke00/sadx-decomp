#include "decls.h"
extern int DAT_060b9908;
extern float DAT_060dd890;

// FUNCTION: SADX 0x006c13a0
void BgDisplayer(struct task *tp)
{
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	___njFogDisable();
	___njSetTexture(&texlist_egm1sora);
	njPushMatrix((float *)0);
	FUN_0067d830((float *)0, DAT_05b42a7c->pos.x, 0.0f, DAT_05b42a7c->pos.z);
	njScaleV((float *)0, &DAT_05b3e074);
	ds_DrawObjectClip((struct obj *)&object_mra_s_sora_hare_s_sora_hare, FUN_004a1e90((float *)&DAT_05b3e074));
	njPopMatrix(1);
	___njFogEnable();
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	late_SetFunc((void (__cdecl *)(void *))DrawSaltWater3D_20, &DAT_060dd890, -7952.0f, 1);
}

// FUNCTION: SADX 0x006c1470
void Rd_Bossegm1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetFreeCameraMode(0);
	switch (var1->mode)
	{
	case 0:
		var1 = tp->twp;
		setBoss_egm1();
		SetDisplayBossName("EGG HORNET", -1, 0xf0, 0x78);
		SetEgm1Bgm();
		var1->mode = 1;
		SetFreeCameraMode(0);
		InitIndirectEffect3D_20();
		if (GetCountKilledPlayer() == 0)
		{
			DAT_060b9908 = 0;
		}
		break;
	case 2:
		FUN_007d21b0();
		___njFogDisable();
		break;
	}
}

// STUB: SADX 0x006c14e0
void FUN_006c14e0(struct task *tp)
{
}
