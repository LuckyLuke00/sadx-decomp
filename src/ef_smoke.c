#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
void EffectSmoke(struct sp_task *tp, struct sp_link *lp);
extern "C" int rand(void);

// STUB: SADX 0x005533c0
void EffectSmokeExp(struct sp_task *tp, struct sp_link *lp)
{
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

// STUB: SADX 0x005537c0
void CreateAddSmoke(struct particle_info *effect)
{
}
