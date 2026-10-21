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
		local_8g = local_cg->twp;
		local_8g->pos = twp->pos;
		local_8g->scl.x = scl;
	}
	return;
}

// FUNCTION: SADX 0x005e8280
void FlashManager(struct task *tp)
{
	struct taskwk *local_8g;

	local_8g = *(struct taskwk **)((char *)tp + 0x20);
	switch (local_8g->mode)
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
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;

	local_8gk = particle_flash.link;
	local_ci = SpCreateTask(local_8gk, EffectFlash);
	if (local_ci != NULL)
	{
		local_ci->pos = twp->pos;
		local_ci->scl = twp->scl.x;
		local_ci->frame = 0.0;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->ang = (int)(local_14k * 360.0 * 65536.0 / 360.0);
		local_ci->argb.a = 1.0;
		local_ci->argb.r = 1.0;
		local_ci->argb.g = 1.0;
		local_ci->argb.b = 1.0;
	}
	twp->mode = 1;
}

// FUNCTION: SADX 0x005e83a0
void FlashManagerNormal(struct taskwk *twp)
{
	int local_8gk;
	struct NJS_POINT3 velo;
	int local_1cj;
	float local_20r;
	int local_24h;
	float local_28;
	int local_2cg;
	float local_30i;

	*(float *)((char *)twp + 0x10) = *(float *)((char *)twp + 0x10) + 0.4000000059604645;
	if (*(float *)((char *)twp + 0x10) > 7.0)
	{
		twp->mode = 2;
	}
	else
	{
		for (local_8gk = 0; local_8gk < 3; local_8gk = local_8gk + 1)
		{
			local_1cj = rand();
			local_20r = (float)(local_1cj / 32768.0);
			velo.x = (float)(local_20r * 5.5 - 2.75);
			local_24h = rand();
			local_28 = (float)(local_24h / 32768.0);
			velo.y = (float)(local_28 * 5.5 - 2.0);
			local_2cg = rand();
			local_30i = (float)(local_2cg / 32768.0);
			velo.z = (float)(local_30i * 5.5 - 2.75);
			CreateSpark(&twp->pos, &velo, 1.0);
		}
	}
	return;
}

// FUNCTION: SADX 0x005e84a0
void CreateFlash2(float x, float y, float z, float scl)
{
	struct task *local_cg;
	struct taskwk *local_8g;

	dsPlay_oneshot(0x19, 0, 0, 0);
	local_cg = CreateElementalTask(2, 6, FlashManager);
	if (local_cg != 0)
	{
		local_8g = local_cg->twp;
		local_8g->pos.x = x;
		local_8g->pos.y = y;
		local_8g->pos.z = z;
		local_8g->scl.x = scl;
	}
}
