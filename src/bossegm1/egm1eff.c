#include "decls.h"
extern int *DAT_060b99f4;
void SetEgm1AtkSmoke(struct NJS_POINT3 *posp);
static void egm1ground_smoke_exec(struct task *tp);
extern struct task *DAT_060b99f8;
void egm1ground_smoke_exec(struct task *tp);

// FUNCTION: SADX 0x006c4670
static void egm1ground_smoke_exec(struct task *tp)
{
	struct anywk *var1 = tp->awp;
	struct NJS_POINT3 local_14;
	struct NJS_POINT3 local_20;
	if (var1->work.ub[12])
	{
		FreeTask(tp);
		return;
	}
	{
		int var2 = ZRandomS(0x10000);
		local_14.x = njCos(var2) * 44.0 + var1->work.f[0];
		local_14.y = var1->work.f[1];
		local_14.z = njSin(var2) * 44.0 + var1->work.f[2];
		local_20.x = 0.0f;
		local_20.y = 0.6f;
		local_20.z = 0.0f;
		CreateSmoke(&local_14, &local_20, 3.0f);
	}
}

// FUNCTION: SADX 0x006c4730
void SetEgm1GroundSmoke(struct NJS_POINT3 *posp)
{
	struct task *var1;
	struct Egm1SmokeManWk *var2;

	var1 = CreateElementalTask(0, 3, egm1ground_smoke_exec);
	DAT_060b99f8 = var1;
	if (var1 != NULL)
	{
		var2 = (struct Egm1SmokeManWk *)CAlloc(1, 0x10);
		var1->awp = (struct anywk *)var2;
		var2->Pos = *posp;
		var2->Mode = 0;
		var1->exec = egm1ground_smoke_exec;
	}
}

// FUNCTION: SADX 0x006c4780
void ChgEgm1SmokeStat(unsigned char mode)
{
	*(unsigned char *)((char *)DAT_060b99f8->awp + 0xc) = mode;
}

// FUNCTION: SADX 0x006c4790
void SetEgm1AtkSmoke(struct NJS_POINT3 *posp)
{
	int var1;
	struct NJS_POINT3 local_14;
	struct NJS_POINT3 local_20;

	for (var1 = 4; var1 != 0; var1--)
	{
		int var2 = ZRandomS(0x10000);

		local_14.x = njCos(var2) * 12.0f + posp->x;
		local_14.y = posp->y;
		local_14.z = njSin(var2) * 12.0f + posp->z;
		local_20.x = 0.0f;
		local_20.y = 0.8f;
		local_20.z = 0.0f;
		CreateSmoke(&local_14, &local_20, 20.0f);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x006c4830
void egm1one_clay_disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006c48b0
void ChgEgm1ClayStat(unsigned char mode)
{
	*(unsigned char *)((char *)((struct task *)DAT_060b99f4)->awp + 0x10) = mode;
}

// FUNCTION: SADX 0x006c48c0
void egm1one_clay_exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	var1->pos.x += var2->work.f[2];
	var1->pos.y += var2->work.f[3];
	var1->pos.z += var2->work.f[4];
	var2->work.f[3] -= 0.10000000149011612;
	var1->ang.x += var2->work.ul[5];
	var1->ang.y += var2->work.ul[6];
	var1->ang.z += var2->work.ul[7];
	if (var1->pos.y < 0.0f)
	{
		FreeTask(tp);
		return;
	}
	egm1one_clay_disp(tp);
}

// FUNCTION: SADX 0x006c4b20
void SetEgm1GroundClay(struct NJS_POINT3 *posp)
{
	struct task *var1;
	struct anywk *var2;

	var1 = CreateElementalTask(0, 3, egm1ground_clay_exec);
	DAT_060b99f4 = (int *)var1;
	if (var1 != 0)
	{
		var2 = (struct anywk *)CAlloc(1, 0x14);
		var1->awp = var2;
		*(int *)(var2) = *(int *)(posp);
		*(int *)((char *)var2 + 4) = *(int *)((char *)posp + 4);
		*(int *)((char *)var2 + 8) = *(int *)((char *)posp + 8);
		*(char *)((char *)var2 + 0x10) = 0;
		*(int *)((char *)var2 + 0xc) = 0;
		var1->exec = egm1ground_clay_exec;
	}
}
