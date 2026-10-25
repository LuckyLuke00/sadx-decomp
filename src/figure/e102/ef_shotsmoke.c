#include "decls.h"
#include <stdlib.h>
#include <math.h>

// FUNCTION: SADX 0x005d4e60
void CreateShotsmoke(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_shotsmoke.link;
	local_ci = SpCreateTask(local_8gk, EffectShotsmoke);
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
		local_ci->work[0].ptr = &default_shotsmoke;
	}
}

// STUB: SADX 0x005d4f50
void EffectShotsmoke(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x005d5090
void initShotsmoke()
{
	particle_shotsmoke.link = SpCreateLinkW(particle_shotsmoke.info, 0);
}
