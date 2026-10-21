#include "decls.h"
#include <stdlib.h>
#include <math.h>
struct particle_info;
struct particle_entry;
struct sp_task;
struct sp_link;
extern struct particle_entry particle_snow;
void CreateSnow2(struct particle_info *effect);
extern "C" int rand(void);
extern "C" long _ftol2_sse(float param_1);

// FUNCTION: SADX 0x005b4970
void CreateSnow(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_snow.link;
	local_ci = SpCreateTask(local_8gk, EffectSnow);
	if (local_ci != NULL)
	{
		local_ci->pos = *pos;
		local_ci->spd = *velo;
		local_ci->scl = scl;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 4.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = 0x2000 - (int)(local_1co * 4096.0);
		local_ci->argb.a = 1.0F;
		local_ci->argb.r = 1.0F;
		local_ci->argb.g = 1.0F;
		local_ci->argb.b = 1.0F;
		local_ci->work[0].ptr = &default_snow;
	}
}

// FUNCTION: SADX 0x005b4a60
void EffectSnow(struct sp_task *tp, struct sp_link *lp)
{
	struct sp_link *local_cg;
	float local_8g;

	local_cg = (struct sp_link *)*(int *)((char *)tp + 0x44);
	*(short *)((char *)tp + 0xa) = (short)(int)*(float *)((char *)tp + 0x10);
	if (*(short *)((char *)tp + 0xa) >= 8)
	{
		*(short *)((char *)tp + 0xa) = 7;
		SpFreeTask(tp);
		return;
	}
	*(float *)((char *)tp + 0x10) += *(float *)((char *)local_cg + 8);
	local_8g = *(float *)((char *)local_cg + 0xc);
	*(float *)((char *)tp + 0x24) = -*(float *)((char *)tp + 0x24) * local_8g + *(float *)((char *)tp + 0x24);
	*(float *)((char *)tp + 0x28) = -*(float *)((char *)tp + 0x28) * local_8g + *(float *)((char *)local_cg + 0x10) + *(float *)((char *)tp + 0x28);
	*(float *)((char *)tp + 0x2c) = -*(float *)((char *)tp + 0x2c) * local_8g + *(float *)((char *)tp + 0x2c);
	*(float *)((char *)tp + 0x18) += *(float *)((char *)tp + 0x24);
	*(float *)((char *)tp + 0x1c) += *(float *)((char *)tp + 0x28);
	*(float *)((char *)tp + 0x20) += *(float *)((char *)tp + 0x2c);
	*(float *)((char *)tp + 0x14) += *(float *)((char *)local_cg + 4);
	return;
}

// FUNCTION: SADX 0x005b4b60
void CreateSnow2(struct particle_info *effect)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_snow.link;
	local_ci = SpCreateTask(local_8gk, EffectSnow);
	if (local_ci != NULL)
	{
		local_ci->pos = effect->pos;
		local_ci->spd = effect->velo;
		local_ci->scl = effect->scl;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 4.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = 0x2000 - (int)(local_1co * 4096.0);
		local_ci->argb = effect->argb;
		local_ci->work[0].ptr = effect;
	}
}
