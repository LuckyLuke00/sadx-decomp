#include "decls.h"
void Egm3_bakucolorExit(struct task *tp);
void addColorR(int r);
extern union NJS_COLOR DAT_060bb188[12];
void Egm3_kogeDraw(struct task *tp);
void FreeTask(struct task *tp);
extern unsigned char DAT_060bb21c;

// STUB: SADX 0x006ce190
void Egm3komaDraw(struct task *tp)
{
}

// STUB: SADX 0x006ce430
void Egm3sippoHakai(struct task *tp)
{
}

// STUB: SADX 0x006ce4a0
void Egm3_laser1Draw(struct task *tp)
{
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

// STUB: SADX 0x006ce8d0
void EggmanEnergyDraw(struct task *tp)
{
}

// STUB: SADX 0x006ce9b0
void EggmanBoomerangDraw(struct task *tp)
{
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

// STUB: SADX 0x006ced40
void Egm3_bakucolorExit(struct task *tp)
{
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

// STUB: SADX 0x006d11a0
void FUN_006d11a0(struct task *tp)
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

// STUB: SADX 0x006d2b00
void Egm3_bakucolor(struct task *tp)
{
}

// STUB: SADX 0x006d2bb0
void Egm3_bakucolor2(struct task *tp)
{
}

// STUB: SADX 0x006d2c90
void Egm3_firecolor2(struct task *tp)
{
}
