#include "decls.h"
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT2 DAT_05b3e080;
extern struct taskwk *DAT_05b42a7c;
extern struct obj object_ecsc_s_sora_hare_robo;
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_b_robo_bg;

// FUNCTION: SADX 0x006d6660
void BgDestructor(struct task *tp)
{
	late_ReleaseTexture(&texlist_b_robo_bg);
}

// FUNCTION: SADX 0x006d6670
void DisplayFineSky(struct taskwk *twp)
{
	if (!DAT_05b9d838)
	{
		FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
		SaveControl3D();
		SaveConstantAttr();
		OffControl3D(0x40);
		OnControl3D(0x14);
		OnConstantAttr(0, 0x2000000);
		___njFogDisable();
		___njSetTexture(&texlist_b_robo_bg);
		SetMaterial(0, 0.8f, 0.8f, 0.8f);
		njPushMatrix(0);
		FUN_0067d830(0, DAT_05b42a7c->pos.x, 0, DAT_05b42a7c->pos.z);
		ds_DrawObjectClip(&object_ecsc_s_sora_hare_robo, 1.0f);
		njPopMatrix(1);
		___njFogEnable();
		LoadConstantAttr();
		LoadControl3D();
		FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	}
	ResetMaterial();
}

// STUB: SADX 0x006d67d0
void BgDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x006d6800
void Rd_BossRobo(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetFreeCameraMode(0);
	var1->mode++;
	if (var1->mode >= 2)
	{
		var1->mode = 0;
		tp->exec = BossRoboExec;
	}
}
