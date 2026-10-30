#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
void EffectSmoke(struct sp_task *tp, struct sp_link *lp);
extern "C" int rand(void);

// FUNCTION: SADX 0x005533c0
void EffectSmokeExp(struct sp_task *tp, struct sp_link *lp)
{
	*(short *)((char *)tp + 0xa) = (short)(int)*(float *)((char *)tp + 0x10);
	if (*(short *)((char *)tp + 0xa) >= *(short *)((char *)*(int *)((char *)lp + 0x10) + 8))
	{
		*(short *)((char *)tp + 0xa) = *(short *)((char *)*(int *)((char *)lp + 0x10) + 8) - 1;
		SpFreeTask(tp);
		return;
	}
	if (*(float *)((char *)tp + 0x10) < 6.0)
	{
		*(float *)((char *)tp + 0x10) += 0.1899999976158142;
	}
	else
	{
		*(float *)((char *)tp + 0x10) += 0.5699999928474426;
	}
	*(float *)((char *)tp + 0x14) += 0.00570000009611249;
	*(float *)((char *)tp + 0x1c) += 0.30000001192092896;
	*(float *)((char *)tp + 0x20) += 0.10000000149011612;
	return;
}

// FUNCTION: SADX 0x00553480
void EffectSmoke(struct sp_task *tp, struct sp_link *lp)
{
	struct sp_link *local_cg;
	float local_8g;

	local_cg = (struct sp_link *)*(int *)((char *)tp + 0x44);
	*(short *)((char *)tp + 0xa) = (short)(int)*(float *)((char *)tp + 0x10);
	if (*(short *)((char *)tp + 0xa) >= *(short *)((char *)*(int *)((char *)lp + 0x10) + 8))
	{
		*(short *)((char *)tp + 0xa) = *(short *)((char *)*(int *)((char *)lp + 0x10) + 8) - 1;
		SpFreeTask(tp);
		return;
	}
	if (*(float *)((char *)tp + 0x10) < 6.0)
	{
		*(float *)((char *)tp + 0x10) += *(float *)((char *)local_cg + 8);
	}
	else
	{
		*(float *)((char *)tp + 0x10) = *(float *)((char *)local_cg + 8) * 2.0 + *(float *)((char *)tp + 0x10);
	}
	local_8g = *(float *)((char *)local_cg + 0xc);
	*(float *)((char *)tp + 0x24) = -*(float *)((char *)tp + 0x24) * local_8g + *(float *)((char *)tp + 0x24);
	*(float *)((char *)tp + 0x28) = -*(float *)((char *)tp + 0x28) * local_8g + *(float *)((char *)local_cg + 0x10) + *(float *)((char *)tp + 0x28);
	*(float *)((char *)tp + 0x2c) = -*(float *)((char *)tp + 0x2c) * local_8g + *(float *)((char *)tp + 0x2c);
	*(float *)((char *)tp + 0x18) += *(float *)((char *)tp + 0x24);
	*(float *)((char *)tp + 0x1c) += *(float *)((char *)tp + 0x28);
	*(float *)((char *)tp + 0x20) += *(float *)((char *)tp + 0x2c);
	*(float *)((char *)tp + 0x14) += *(float *)((char *)local_cg + 4) * 0.15000000596046448;
	return;
}

// FUNCTION: SADX 0x005535c0
void CreateSmoke(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_smoke.link;
	local_ci = SpCreateTask(local_8gk, EffectSmoke);
	if (local_ci != NULL)
	{
		local_ci->pos = *pos;
		local_ci->spd = *velo;
		local_ci->scl = scl * 0.15f;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 6.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 360.0) * 65536.0 / 360.0);
		local_ci->argb.a = 1.0;
		local_ci->argb.r = 1.0;
		local_ci->argb.g = 1.0;
		local_ci->argb.b = 1.0;
		local_ci->work[0].ptr = &default_smoke;
	}
}

// FUNCTION: SADX 0x005537c0
void CreateAddSmoke(struct particle_info *effect)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_addsmoke.link;
	local_ci = SpCreateTask(local_8gk, EffectSmoke);
	if (local_ci != NULL)
	{
		local_ci->pos = effect->pos;
		local_ci->spd = effect->velo;
		local_ci->scl = effect->scl * 0.15000000596046448;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 6.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 360.0) * 65536.0 / 360.0);
		local_ci->argb = effect->argb;
		local_ci->work[0].ptr = effect;
	}
}
