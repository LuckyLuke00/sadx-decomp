#include "decls.h"
#include <stdlib.h>
void FlashManagerNormal(struct taskwk *twp);
struct task;
struct taskwk;
void FlashManagerInit(struct taskwk *);
void FlashManagerNormal(struct taskwk *);
void FreeTask(struct task *);
void CreateFlash(struct taskwk *twp, float scl);

// FUNCTION: SADX 0x005e81c0
void EffectFlash(struct sp_task *tp, struct sp_link *lp)
{
	*(short *)((char *)tp + 0xa) = (short)(int)*(float *)((char *)tp + 0x10);
	if (*(short *)((char *)tp + 0xa) > 7)
	{
		*(short *)((char *)tp + 0xa) = 7;
		SpFreeTask(tp);
	}
	else
	{
		*(float *)((char *)tp + 0x10) = *(float *)((char *)tp + 0x10) + 0.4f;
	}
}

// FUNCTION: SADX 0x005e8210
void CreateFlash(struct taskwk *twp, float scl)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	dsPlay_oneshot(0x19, 0, 0, 0);
	local_cg = CreateElementalTask(2, 6, FlashManager);
	if (local_cg != 0)
	{
		local_8g = (struct taskwk *)(*(int *)(*(char **)local_cg + 0x20) + 0x20);
		*(int *)local_8g = *(int *)((char *)twp + 0x20);
		*(int *)(local_8g + 1) = *(int *)((char *)twp + 0x24);
		*(int *)(local_8g + 2) = *(int *)((char *)twp + 0x28);
		*(float *)(local_8g + 3) = scl;
	}
	return;
}

// FUNCTION: SADX 0x005e8280
void FlashManager(struct task *tp)
{
	struct taskwk *local_8g;
	char local_9;

	local_8g = *(struct taskwk **)((char *)tp + 0x20);
	local_9 = *(char *)local_8g;
	switch (local_9)
	{
		case 0:
			FlashManagerInit(local_8g);
			break;
		case 1:
			FlashManagerNormal(local_8g);
			break;
		case 2:
			FreeTask(tp);
			break;
	}
}

// FUNCTION: SADX 0x005e82e0
void FlashManagerInit(struct taskwk *twp)
{
	struct sp_task *local_14;
	int iVar2;
	double dVar3;

	local_14 = SpCreateTask((struct sp_link *)&particle_flash, EffectFlash);
	if (local_14 != NULL)
	{
		*(int *)((char *)local_14 + 0x18) = *(int *)((char *)twp + 0x20);
		*(int *)((char *)local_14 + 0x1c) = *(int *)((char *)twp + 0x24);
		*(int *)((char *)local_14 + 0x20) = *(int *)((char *)twp + 0x28);
		*(float *)((char *)local_14 + 0x14) = *(float *)((char *)twp + 0x2c);
		*(float *)((char *)local_14 + 0x10) = 0.0;
		iVar2 = rand();
		dVar3 = ((double)(float)(iVar2 / 32768.0f)) * 360.0 * 65536.0 / 360.0;
		*(int *)((char *)local_14 + 0xc) = (int)dVar3;
		*(float *)((char *)local_14 + 0x30) = 1.0;
		*(float *)((char *)local_14 + 0x34) = 1.0;
		*(float *)((char *)local_14 + 0x38) = 1.0;
		*(float *)((char *)local_14 + 0x3c) = 1.0;
	}
	*(char *)twp = 1;
}

// FUNCTION: SADX 0x005e83a0
void FlashManagerNormal(struct taskwk *twp)
{
	int local_8g;
	float local_14h;
	float local_10m;
	float local_cj;
	int local_18;

	*(float *)((char *)twp + 0x10) = *(float *)((char *)twp + 0x10) + 0.4000000059604645;
	if (*(float *)((char *)twp + 0x10) > 7.0)
	{
		*(char *)twp = 2;
	}
	else
	{
		for (local_18 = 0; local_18 < 3; local_18 = local_18 + 1)
		{
			local_8g = rand();
			local_14h = ((float)local_8g / 32768.0) * 5.5 - 2.75;
			local_8g = rand();
			local_10m = ((float)local_8g / 32768.0) * 5.5 - 2.0;
			local_8g = rand();
			local_cj = ((float)local_8g / 32768.0) * 5.5 - 2.75;
			CreateSpark((struct NJS_POINT3 *)((char *)twp + 0x20), (struct NJS_POINT3 *)&local_14h, 1.0);
		}
	}
	return;
}

// FUNCTION: SADX 0x005e84a0
void CreateFlash2(float x, float y, float z, float scl)
{
	dsPlay_oneshot(0x19, 0, 0, 0);
	struct task *local_8 = CreateElementalTask(2, 6, FlashManager);
	if (local_8 != 0)
	{
		struct task *local_c = *(struct task **)((char *)local_8 + 0x20);
		*(float *)((char *)local_c + 0x20) = x;
		*(float *)((char *)local_c + 0x24) = y;
		*(float *)((char *)local_c + 0x28) = z;
		*(float *)((char *)local_c + 0x2c) = scl;
	}
}
