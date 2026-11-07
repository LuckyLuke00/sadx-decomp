#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
extern struct CCL_INFO colliInfo[1];
extern struct taskwk *DAT_060b9b10;
extern float DAT_060b9b00;
extern float DAT_060b9b04;
extern float DAT_060b9b08;
extern int DAT_060b9aa0;
extern int DAT_060b9ab0;
void FUN_006c7ea0();
extern "C" double atan2(double v, double u);
extern int DAT_060b9abc;
extern struct _camcontwk *camcont_wp;
extern struct NJS_TEXLIST texlist_egm2_sky;
extern struct obj object_boss_em2_sky_n_sky_n[1];
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT2 DAT_05b3e080;
extern int DAT_05b9d838;
extern int DAT_060b9ab4;
extern int DAT_060b9a8c;
extern int DAT_060b9ae4;
extern float DAT_060b9b2c;
extern int DAT_060b9b34;

#pragma optimize("", off)
// STUB: SADX 0x006c7740
void FUN_006c7740(void)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006c7d40
void FUN_006c7d40(void)
{
	struct _camcontwk *var1;
	struct _camcontwk *var2;
	struct _camcontwk *var3;
	var1 = camcont_wp;
	if (*(float *)((char *)var1 + 0x10) < 2.5f)
	{
		*(float *)((char *)var1 + 0x10) = 2.5f;
	}
	var2 = camcont_wp;
	if (*(float *)((char *)var2 + 0xc) < -537.0f)
	{
		*(float *)((char *)var2 + 0xc) = -537.0f;
	}
	if (*(float *)((char *)var2 + 0xc) > -350.0f)
	{
		*(float *)((char *)var2 + 0xc) = -350.0f;
	}
	var3 = camcont_wp;
	if (*(float *)((char *)var3 + 0x14) < 910.0f)
	{
		*(float *)((char *)var3 + 0x14) = 910.0f;
	}
	if (*(float *)((char *)var3 + 0x14) > 1500.0f)
	{
		*(float *)((char *)var3 + 0x14) = 1500.0f;
	}
	DAT_060b9b00 = *(float *)((char *)var2 + 0xc);
	DAT_060b9b04 = *(float *)((char *)var1 + 0x10);
	DAT_060b9b08 = *(float *)((char *)var3 + 0x14);
}

// FUNCTION: SADX 0x006c7df0
void egm2_sky_display()
{
	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_egm2_sky);
	njPushMatrix(0);
	FUN_0067d830(0, *(float *)((char *)camcont_wp + 0xc), *(float *)((char *)camcont_wp + 0x10), *(float *)((char *)camcont_wp + 0x14));
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	ds_DrawObjectClip(&object_boss_em2_sky_n_sky_n[0], 1.0);
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006c7e80
void Egm2CameraYurashi(unsigned char level)
{
	DAT_060b9b2c += (float)level * 0.5;
}

// FUNCTION: SADX 0x006c7f70
long Egm2CameraHumiCameraGet()
{
	return DAT_060b9b34;
}

// FUNCTION: SADX 0x006c7f80
void Egm2CameraTaoreSet()
{
	DAT_060b9ab4 = 1;
	DAT_060b9a8c = 1;
	DAT_060b9ae4 = 1;
}

// FUNCTION: SADX 0x006c82d0
void FUN_006c82d0(void)
{
	struct task *local_4;
	struct taskwk *local_8;

	local_4 = CreateElementalTask(2, 3, (void (__cdecl *)(struct task *))FUN_006877a0);
	if (local_4 != NULL)
	{
		local_8 = local_4->twp;
		EnemyInitialize(local_4, local_8);
		local_8->pos = DAT_05baf368[0]->pos;
		local_4->exec = (void (__cdecl *)(struct task *))FUN_006877a0;
		CCL_Init(local_4, (struct CCL_INFO *)&colliInfo, 1, 5);
		DAT_060b9b10 = (struct taskwk *)&local_8->pos;
	}
}

// FUNCTION: SADX 0x006c8330
struct taskwk *Egm2StartPositionTask(struct NJS_POINT3 *pos)
{
	struct task *var1;
	struct taskwk *var2;
	var1 = CreateElementalTask(2, 3, (void (__cdecl *)(struct task *))FUN_007d21b0);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->pos = *pos;
		var2->pos.y += 40.0;
		var1->exec = (void (__cdecl *)(struct task *))FUN_007d21b0;
		return var2;
	}
	return 0;
}

// FUNCTION: SADX 0x006c8420
void egm2_camera(struct _OBJ_CAMERAPARAM *pParam)
{
	DAT_060b9ab0 = -16384 - (int)(atan2(*(float *)((char *)camcont_wp + 0x20) - *(float *)((char *)camcont_wp + 0x14), *(float *)((char *)camcont_wp + 0x18) - *(float *)((char *)camcont_wp + 0xc)) * 65536.0 / 6.283184);
	egm2_player_position();
	FUN_006c7740();
	if (DAT_060b9abc == 1 || DAT_060b9ab4 == 1)
	{
		egm2_near_camera();
	}
	else
	{
		egm2_far_camera();
	}
	FUN_006c7ea0();
	egm2_calc_camera();
	FUN_006c7d40();
	DAT_060b9aa0 = 0;
	DAT_060b9ab4 = 0;
	DAT_060b9ae4 = 0;
}
