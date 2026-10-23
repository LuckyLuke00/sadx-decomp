#include "decls.h"
extern "C" int rand(void);

// FUNCTION: SADX 0x005536c0
void FUN_005536c0(struct particle_info *param_1)
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
		local_ci->pos = param_1->pos;
		local_ci->spd = param_1->velo;
		local_ci->scl = param_1->scl * 0.15000000596046448;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 6.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 360.0) * 65536.0 / 360.0);
		local_ci->argb = param_1->argb;
		local_ci->work[0].ptr = param_1;
	}
}
