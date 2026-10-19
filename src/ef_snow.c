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
	struct sp_link *local_18;
	struct sp_task *local_1c;
	int local_8g;
	float local_14;
	int local_cj;
	float local_10;

	local_18 = (struct sp_link *)&particle_snow;
	local_1c = SpCreateTask(local_18, EffectSnow);
	if (local_1c != NULL)
	{
		*(float *)((char *)local_1c + 0x18) = pos->x;
		*(float *)((char *)local_1c + 0x1c) = pos->y;
		*(float *)((char *)local_1c + 0x20) = pos->z;
		*(float *)((char *)local_1c + 0x24) = velo->x;
		*(float *)((char *)local_1c + 0x28) = velo->y;
		*(float *)((char *)local_1c + 0x2c) = velo->z;
		*(float *)((char *)local_1c + 0x14) = scl;
		local_8g = rand();
		local_14 = (float)local_8g / 32768.0F;
		local_14 = local_14 * 4.0F;
		*(float *)((char *)local_1c + 0x10) = local_14;
		local_cj = rand();
		local_10 = (float)local_cj / 32768.0F;
		*(int *)((char *)local_1c + 0x0c) = 0x2000 - _ftol2_sse(local_10 * 4096.0F);
		*(float *)((char *)local_1c + 0x30) = 1.0F;
		*(float *)((char *)local_1c + 0x34) = 1.0F;
		*(float *)((char *)local_1c + 0x38) = 1.0F;
		*(float *)((char *)local_1c + 0x3c) = 1.0F;
		*(struct particle_info **)((char *)local_1c + 0x44) = &default_snow;
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
	struct sp_task *local_14h;
	int local_10m;
	int local_8g;
	int local_cj;
	int local_18;

	local_14h = SpCreateTask((struct sp_link *)&particle_snow + 1, EffectSnow);
	if (local_14h != NULL)
	{
		*(int *)((char *)local_14h + 0x18) = *(int *)((char *)effect + 0x14);
		*(int *)((char *)local_14h + 0x1c) = *(int *)((char *)effect + 0x18);
		*(int *)((char *)local_14h + 0x20) = *(int *)((char *)effect + 0x1c);
		*(int *)((char *)local_14h + 0x24) = *(int *)((char *)effect + 0x20);
		*(int *)((char *)local_14h + 0x28) = *(int *)((char *)effect + 0x24);
		*(int *)((char *)local_14h + 0x2c) = *(int *)((char *)effect + 0x28);
		*(int *)((char *)local_14h + 0x14) = *(int *)((char *)effect + 0x0);
		local_10m = rand();
		local_cj = (int)(local_10m / 32768.0);
		*(int *)((char *)local_14h + 0x10) = local_cj * 4;
		local_8g = rand();
		local_18 = (int)(local_8g / 32768.0 * 4096.0);
		*(int *)((char *)local_14h + 0xc) = 0x2000 - local_18;
		*(int *)((char *)local_14h + 0x30) = *(int *)((char *)effect + 0x2c);
		*(int *)((char *)local_14h + 0x34) = *(int *)((char *)effect + 0x30);
		*(int *)((char *)local_14h + 0x38) = *(int *)((char *)effect + 0x34);
		*(int *)((char *)local_14h + 0x3c) = *(int *)((char *)effect + 0x38);
		*(struct particle_info **)((char *)local_14h + 0x44) = effect;
	}
}
