#include "decls.h"
static void Disp(struct task *tp);
static void BuilGDisp(struct task *tp);
static void Exec(struct task *tp);
static void BuilGExec(struct task *tp);
static void BuilGInit(struct task *tp);
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern struct obj object_casinoobj_builg_builg[1];

// GLOBAL: SADX 0x026daf38
static struct obj *objs[3] = {object_cajinoobj_casinostar_casinostar, object_casinoobj_builh_builh, object_casinoobj_casinoji_casinoji};

// GLOBAL: SADX 0x026daf44
static struct uv_info uv_neon0_v[1] = {{vuvS_2_casinoobj_casinobuil_nc_casinosim, 70}};

// GLOBAL: SADX 0x026daf4c
static struct neon_info neon0_v = {uv_neon0_v, 1, 4, 45, 9, 0, 0};

// GLOBAL: SADX 0x026daf5c
static struct uv_info uv_neon1_v[3] = {{vuvS_1_casinoobj_casinobuil_nc_casinoneon, 12}, {vuvS_1_casinoobj_casinobuil_nc_casinosim, 16}, {vuvS_2_casinoobj_casinobuil_es_casinoyane, 16}};

// GLOBAL: SADX 0x026daf74
static struct neon_info neon1_v = {uv_neon1_v, 3, 12, 45, 9, 0, 0};

// GLOBAL: SADX 0x026daf84
static struct uv_info uv_neon5_v[1] = {{vuvS_0_casinoobj_builh_builhkabe, 96}};

// GLOBAL: SADX 0x026daf8c
static struct neon_info neon5_v = {uv_neon5_v, 1, 12, 45, 9, 0, 0};

#pragma optimize("", off)
// STUB: SADX 0x006821d0
void SetMatAttribute(struct obj *op, unsigned long attr)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00682220
void ResetMatAttribute(struct obj *op, unsigned long attr)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00682270
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ss_casino);
		SaveControl3D();
		SaveConstantAttr();
		OnControl3D(4);
		if (var1->smode == 0)
		{
			OnConstantAttr(0, 0x2000000);
			OffConstantAttr(0x2000000, 0);
		}
		else
		{
			OnConstantAttr(0x2000000, 0);
			OffConstantAttr(0, 0x2000000);
		}
		ds_DrawObjectClip(&object_casinoobj_casinobuil_casinobuil[0], 1.0f);
		LoadConstantAttr();
		LoadControl3D();
		FUN_00422560(3);
		for (int var2 = 0; var2 < 3; var2++)
		{
			ds_DrawObjectClip(objs[var2], 1.0f);
		}
		npSetZCompare();
	}
}

// STUB: SADX 0x00682330
static void BuilGDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x00682460
void DispDay(struct task *tp)
{
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ss_casino);
		FUN_00422560(3);
		for (int var1 = 0; var1 < 3; var1++)
		{
			ds_DrawObjectClip(objs[var1], 1.0f);
		}
		npSetZCompare();
		ds_DrawObjectClip(&object_casinoobj_casinobuil_casinobuil[0], 1.0f);
		ds_DrawObjectClip(&object_casinoobj_builg_builg[0], 1.0f);
	}
}

// The game's link folded this copy into the one of o_egm2_casinokazari.c (0x006c7000).
static void UVScroll(struct neon_info *neon)
{
	short var0 = neon->timer + 1;

	if (var0 > neon->wait_max)
	{
		short var1 = neon->uv_spd;
		short var2 = neon->uv + neon->uv_spd;
		short var3;
		if (var2 > 255)
		{
			var2 -= 256;
			var3 = var1 - 256;
		}
		else
		{
			var3 = var1;
		}
		neon->uv = var2;
		if (!(neon->type & 8))
		{
			var3 = -var3;
		}
		if (neon->type & 2)
		{
			for (int var4 = 0; var4 < neon->info_num; var4++)
			{
				union NJS_COLOR *var5 = neon->info[var4].uv_list;
				short var6 = neon->info[var4].uv_num;
				for (int var7 = 0; var7 < var6; var7++)
				{
					var5->tex.u += var3;
					var5++;
				}
			}
		}
		else if (neon->type & 4)
		{
			for (int var4 = 0; var4 < neon->info_num; var4++)
			{
				union NJS_COLOR *var5 = neon->info[var4].uv_list;
				short var6 = neon->info[var4].uv_num;
				for (int var7 = 0; var7 < var6; var7++)
				{
					var5->tex.v += var3;
					var5++;
				}
			}
		}
		var0 = 0;
	}
	neon->timer = var0;
}

// FUNCTION: SADX 0x006824d0
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->wtimer != (DAT_05b9d724 << 8 | DAT_05b9d744))
	{
		FreeTask(tp);
		return;
	}
	switch (var1->mode)
	{
	case 0:
		if (++var1->timer.l > 360)
		{
			var1->timer.l = 0;
			var1->mode = 1;
			var1->smode = 0;
		}
		else
		{
			var1->smode = var1->timer.l % 60 >= 30;
		}
		break;
	case 1:
		if (++var1->timer.l > 360)
		{
			var1->timer.l = 0;
			var1->mode = 0;
		}
		UVScroll(&neon0_v);
		UVScroll(&neon1_v);
		break;
	}
	UVScroll(&neon5_v);
	Disp(tp);
	LoopTaskC(tp);
}

// STUB: SADX 0x00682580
static void BuilGExec(struct task *tp)
{
}

// FUNCTION: SADX 0x00682740
void ExecDay(struct task *tp)
{
	DispDay(tp);
}

// FUNCTION: SADX 0x00682750
static void BuilGInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->mode = 0;
	var1->wtimer = 0;
	var1->btimer = 0;
	ResetMatAttribute(&object_casinoobj_builg_builg[0], 0xfdffffff);
	tp->exec = BuilGExec;
	tp->disp = BuilGDisp;
}

// FUNCTION: SADX 0x00682790
void ObjectSSCasinokazari(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->ang.x = 0;
	var1->ang.y = 0;
	var1->ang.z = 0;
	var1->mode = 1;
	var1->wtimer = (short)(DAT_05b9d724 << 8 | DAT_05b9d744);
	var1->smode = 0;
	var1->timer.l = 0;
	if (SeqGetTime() == 2)
	{
		CreateChildTask(2, BuilGInit, tp);
		ResetMatAttribute(&object_casinoobj_casinobuil_casinobuil[0], 0xfdffffff);
		SetMatAttribute(&object_cajinoobj_casinostar_casinostar[0], 0x2000000);
		SetMatAttribute(&object_casinoobj_builg_builg[0], 0x2000000);
		SetMatAttribute(&object_casinoobj_builh_builh[0], 0x2000000);
		SetMatAttribute(&object_casinoobj_casinoji_casinoji[0], 0x2000000);
		tp->exec = Exec;
		tp->disp = Disp;
		tp->dest = ExplosionRockDestructor;
	}
	else
	{
		ResetMatAttribute(&object_cajinoobj_casinostar_casinostar[0], 0xfdffffff);
		ResetMatAttribute(&object_casinoobj_builg_builg[0], 0xfdffffff);
		ResetMatAttribute(&object_casinoobj_builh_builh[0], 0xfdffffff);
		ResetMatAttribute(&object_casinoobj_casinobuil_casinobuil[0], 0xfdffffff);
		ResetMatAttribute(&object_casinoobj_casinoji_casinoji[0], 0xfdffffff);
		tp->exec = ExecDay;
		tp->disp = DispDay;
	}
}
