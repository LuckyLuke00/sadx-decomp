#include "decls.h"
extern struct task *DAT_060ccdc8;

// FUNCTION: SADX 0x007de620
void __fastcall FUN_007de620(void *param_1)
{
	float var1 = *(float *)((char *)param_1 + 0xc) + 0.09000000357627869;

	*(float *)((char *)param_1 + 0xc) = var1;
	*(float *)((char *)param_1 + 0x24) = *(float *)((char *)param_1 + 0x24) - var1;
	if (*(float *)((char *)param_1 + 0x24) < *(float *)((char *)param_1 + 0x10))
	{
		*(char *)param_1 = 2;
		*(float *)((char *)param_1 + 0x24) = *(float *)((char *)param_1 + 0x10);
	}
}

// FUNCTION: SADX 0x007de960
void EV_eggmoble2(float x, float y, float z, long ax, long ay, long az)
{
	struct task *var1;
	struct taskwk *var2;
	struct motionwk *var3;

	var1 = CreateElementalTask(3, 5, eggmoble2_exec);
	if (var1)
	{
		var2 = var1->twp;
		var2->pos.x = x;
		var2->ang.x = ax;
		var2->pos.y = y;
		var2->ang.y = ay;
		var2->pos.z = z;
		var2->mode = 0;
		var2->btimer = 1;
		var2->ang.z = az;
		var3 = var1->mwp;
		var3->work.f = 0.0f;
		DAT_060ccdc8 = var1;
		var3->rad = 0.0f;
	}
}

// FUNCTION: SADX 0x007de9c0
void ChgEgg2Mod(signed char mode)
{
	DAT_060ccdc8->twp->mode = mode;
}

// FUNCTION: SADX 0x007de9d0
void EV_deleggmoble2()
{
	if (DAT_060ccdc8)
	{
		FreeTask(DAT_060ccdc8);
		DAT_060ccdc8 = 0;
	}
}

// STUB: SADX 0x007de9f0
void ShadowEggmoble2(float size, float hight)
{
}
