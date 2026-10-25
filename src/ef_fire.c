#include "decls.h"
extern "C" int rand(void);

// FUNCTION: SADX 0x005539d0
void CreateFire(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_fire.link;
	local_ci = SpCreateTask(local_8gk, EffectFire);
	if (local_ci != NULL)
	{
		local_ci->pos = *pos;
		local_ci->spd = *velo;
		local_ci->scl = scl * 0.15000000596046448;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 5.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 160.0 + 100.0) * 65536.0 / 360.0);
		local_ci->argb = default_fire.argb;
		local_ci->work[0].ptr = &default_fire;
	}
}
