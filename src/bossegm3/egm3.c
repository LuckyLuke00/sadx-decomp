#include "decls.h"
extern void *DAT_060bb218;
extern struct LE_LIGHT_ENV DAT_05b39bf0[4];
extern struct obj *DAT_02833c70;
extern struct obj *egm3_object_list[];
extern int DAT_060ba04c;
extern struct NJS_TEXLIST texlist_egm3mdl;
extern struct NJS_TEXLIST *egm3_effect_texlist_list;
extern struct obj *egm3_effect_objectlist[1];
extern int DAT_05b9d838;
static void TikalTaskExit(struct task *tp);
extern int DAT_060bb24c;
extern int DAT_060bb290;
extern struct anywk *DAT_060ba008;
void Egm3_bakucolorExit(struct task *tp);
void addColorR(int r);
extern union NJS_COLOR DAT_060bb188[12];
void Egm3_kogeDraw(struct task *tp);
void FreeTask(struct task *tp);
extern unsigned char DAT_060bb21c;

// FUNCTION: SADX 0x006cdda0
static void TikalTaskExit(struct task *tp)
{
	DAT_060bb24c = 0;
}

// STUB: SADX 0x006ce190
void Egm3komaDraw(struct task *tp)
{
}

// STUB: SADX 0x006ce280
void Egm3komaHakai(struct task *tp)
{
}

// STUB: SADX 0x006ce430
void Egm3sippoHakai(struct task *tp)
{
}

// FUNCTION: SADX 0x006ce4a0
void Egm3_laser1Draw(struct task *tp)
{
	struct taskwk *var1;
	struct anywk *var2;
	float var3;

	var1 = tp->twp;
	var2 = tp->awp;
	switch (DAT_05b9d838)
	{
	case 0:
		SaveConstantAttr();
		___njSetTexture(egm3_effect_texlist_list);
		njPushMatrix(NULL);
		FUN_0067d830(NULL, var1->pos.x, var1->pos.y, var1->pos.z);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, var1->ang.y);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		FUN_0067d2d0(NULL, 1.0f, 1.0f, var2->work.f[2]);
		FUN_0067d830(NULL, 0.0f, 0.0f, 18.929506f);
		if (1.0 > var2->work.f[2])
		{
			var3 = 1.0f;
		}
		else
		{
			var3 = var2->work.f[2];
		}
		late_DrawObjectClip(egm3_effect_objectlist[0], 4, var3);
		njPopMatrix(1);
		LoadConstantAttr();
		break;
	}
}

// STUB: SADX 0x006ce5a0
void Egm3_laser1ponDraw(struct task *tp)
{
}

// FUNCTION: SADX 0x006ce670
void Egm3_energyballExit(struct task *tp)
{
	DAT_060bb21c = 0;
}

// FUNCTION: SADX 0x006ce8d0
void EggmanEnergyDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (DAT_060ba04c == 0)
	{
		return;
	}
	SaveConstantAttr();
	___njSetTexture(&texlist_egm3mdl);
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	if (var1->ang.x)
	{
		njRotateX(0, var1->ang.x);
	}
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
	}
	njRotateY(0, 0x8000);
	late_DrawMotionClipEx(egm3_object_list[5], *(struct NJS_MOTION **)((char *)var2 + 0x6c), *(float *)((char *)var2 + 0x78), 1, 1.0f);
	njPopMatrix(1);
	LoadConstantAttr();
}

// FUNCTION: SADX 0x006ce9b0
void EggmanBoomerangDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	if (DAT_05b9d838 == 0)
	{
		if (DAT_060ba04c != 0)
		{
			SaveConstantAttr();
			___njSetTexture(&texlist_egm3mdl);
			njPushMatrix((float *)0);
			FUN_0067d830((float *)0, var1->pos.x, var1->pos.y, var1->pos.z);
			if (*(int *)((char *)var1 + 0x18) != 0)
			{
				njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
			}
			if (*(int *)((char *)var1 + 0x14) != 0)
			{
				njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
			}
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ((float *)0, *(unsigned short *)((char *)var1 + 0x1c));
			}
			late_DrawMotionClipEx(DAT_02833c70, (struct NJS_MOTION *)*(int *)((char *)var2 + 0x6c), *(float *)((char *)var2 + 0x78), 1, 1.0f);
			njPopMatrix(1);
			LoadConstantAttr();
		}
	}
}

// FUNCTION: SADX 0x006cea80
void FUN_006cea80(void *param_1)
{
	PadReadOn();
}

// FUNCTION: SADX 0x006cecb0
void Egm3_iroiroExit(struct task *tp)
{
	int var1;
	for (var1 = 0; var1 < 12; var1++)
		vuvS_0_kemuri_boss_boss[var1] = DAT_060bb188[var1];
}

// FUNCTION: SADX 0x006ced40
void Egm3_bakucolorExit(struct task *tp)
{
	DAT_060bb290 = 0;
	if (DAT_060bb218 != NULL)
	{
		*(struct LE_LIGHT_ENV *)DAT_05b39bf0 = *(struct LE_LIGHT_ENV *)DAT_060bb218;
	}
	DAT_05b39bf0[1].flgs = 0;
}

// STUB: SADX 0x006cf670
long Egm3TurnToward(long src, long dst, long spd)
{
	return (long)0;
}

// FUNCTION: SADX 0x006cf9b0
int __fastcall FUN_006cf9b0(void *param_1)
{
	float var1 = *(float *)((char *)param_1 + 0x78) - *(float *)((char *)param_1 + 0x7c);

	*(float *)((char *)param_1 + 0x78) = var1;
	if (var1 <= 0.0f)
	{
		*(float *)((char *)param_1 + 0x78) = 0.0f;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x006cfc30
void TikalTask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->mode == 0)
	{
		tp->dest = TikalTaskExit;
		tp->disp = 0;
		var1->mode = var1->mode + 1;
		DAT_060bb24c = 1;
	}
	var1->counter.l = var1->counter.l - 1;
	if (var1->counter.l == 0)
	{
		FreeTask(tp);
	}
}

// STUB: SADX 0x006d11a0
void FUN_006d11a0(struct task *param_1)
{
}

// STUB: SADX 0x006d1210
void FUN_006d1210(struct task *param_1)
{
}

// STUB: SADX 0x006d1280
void Egm3_hibasiraDraw(struct task *tp)
{
}

// STUB: SADX 0x006d1300
void Egm3_kogeDraw(struct task *tp)
{
}

// STUB: SADX 0x006d1320
void Egm3_energyballDraw(struct task *tp)
{
}

// FUNCTION: SADX 0x006d1e10
void SousaFunou(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->mode == 0)
	{
		tp->dest = (void (__cdecl *)(struct task *))FUN_006cea80;
		tp->disp = 0;
		var1->mode = var1->mode + 1;
	}
	PadReadOff();
	var1->counter.l = var1->counter.l - 1;
	if (var1->counter.l == 0)
	{
		FreeTask(tp);
	}
}

// FUNCTION: SADX 0x006d22f0
void addColorR(int r)
{
	addColorRGB((float)r / 255.0, 0.0, 0.0);
	DAT_060bb21c = 0;
}

// STUB: SADX 0x006d25b0
void Egm3_koge(struct task *tp)
{
}

// STUB: SADX 0x006d28c0
void Egm3_energytame(struct task *tp)
{
}

// FUNCTION: SADX 0x006d2a80
void FUN_006d2a80(void)
{
	struct task *var1 = CreateElementalTask(2, 2, EggmanEnergy);
	EnemyInitialize(var1, var1->twp);
	var1->awp = (struct anywk *)CAlloc(1, 0x80);
}

// FUNCTION: SADX 0x006d2ab0
void FUN_006d2ab0(void)
{
	struct task *var1 = CreateElementalTask(2, 2, EggmanBoomerang);
	EnemyInitialize(var1, var1->twp);
	var1->awp = (struct anywk *)CAlloc(1, 0x80);
}

// FUNCTION: SADX 0x006d2ae0
void FUN_006d2ae0(void *param_1)
{
	struct task *var1;
	var1 = CreateElementalTask(2, 1, SousaFunou);
	*(void **)((char *)var1->twp + 8) = param_1;
}

// FUNCTION: SADX 0x006d2b00
void Egm3_bakucolor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		tp->dest = Egm3_bakucolorExit;
		tp->disp = 0;
		if (DAT_060bb290 != 0)
		{
			tp->dest = 0;
			FreeTask(tp);
			return;
		}
		var1->value.l = 0x107;
		DAT_060bb290 = 1;
		break;
	case 1:
		var1->value.l = var1->value.l - 8;
		if (var1->value.l <= 0)
		{
			var1->value.l = 0;
		}
		addColorRGB((float)var1->value.l / 255.0f, 0.0f, 0.0f);
		DAT_060bb21c = 0;
		if (var1->value.l == 0)
		{
			break;
		}
		if (((*(int **)((char *)DAT_060ba008 + 0x2c))[0x64 / 4] & 0x100000) == 0)
		{
			return;
		}
		break;
	default:
		FreeTask(tp);
		return;
	}
	var1->mode = var1->mode + 1;
}

// FUNCTION: SADX 0x006d2bb0
void Egm3_bakucolor2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;
	switch (var1->mode)
	{
	case 0:
		tp->dest = Egm3_bakucolorExit;
		tp->disp = NULL;
		var1->mode++;
		var1->value.l = 0x107;
		break;
	case 1:
		if (DAT_060bb290 == 0)
		{
			var1->mode++;
			DAT_060bb290 = 1;
		}
		break;
	case 2:
		var1->value.l -= 8;
		if (var1->value.l <= 0)
		{
			var1->value.l = 0;
		}
		addColorR(var1->value.l);
		if (var1->value.l <= 0xc0)
		{
			var1->value.l = 0x107;
		}
		if (*(int *)((char *)((struct task *)DAT_060ba008)->awp + 0x64) & 0x200000)
		{
			var1->mode++;
			var1->value.l = 0xc0;
		}
		break;
	case 3:
		var1->value.l += 4;
		if (var1->value.l >= 0x100)
		{
			var1->value.l = 0xff;
		}
		var2 = var1->value.l;
		addColorR(var2);
		if (var1->value.l == 0xff)
		{
			var1->mode++;
		}
		break;
	}
}

// STUB: SADX 0x006d2c90
void Egm3_firecolor2(struct task *tp)
{
}
