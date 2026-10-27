#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
extern struct particle_entry particle_water;
extern "C" int rand(void);

// FUNCTION: SADX 0x005718c0
void CreateWater(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_water.link;
	local_ci = SpCreateTask(local_8gk, EffectWater);
	if (local_ci != NULL)
	{
		local_ci->pos = *pos;
		local_ci->spd = *velo;
		local_ci->scl = scl * 0.17000000178813934;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 5.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 160.0 + 100.0) * 65536.0 / 360.0);
		local_ci->argb = default_water.argb;
		local_ci->work[0].ptr = &default_water;
	}
}

// FUNCTION: SADX 0x005719c0
void CreateWater2(struct particle_info *effect)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_water.link;
	local_ci = SpCreateTask(local_8gk, EffectWater);
	if (local_ci != NULL)
	{
		local_ci->pos = effect->pos;
		local_ci->spd = effect->velo;
		local_ci->scl = effect->scl;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 5.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 160.0 + 100.0) * 65536.0 / 360.0);
		local_ci->argb = effect->argb;
		local_ci->work[0].ptr = effect;
	}
}
