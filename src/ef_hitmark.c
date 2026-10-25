#include "decls.h"
extern struct particle_entry particle_hitmark;
extern void EffectHit(struct sp_task *tp, struct sp_link *lp);
extern struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
extern "C" int rand(void);

// FUNCTION: SADX 0x0060d2b0
void CreateHitmark2(struct particle_info *effect)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;

	local_8gk = particle_hitmark.link;
	local_ci = SpCreateTask(local_8gk, EffectHit);
	if (local_ci != NULL)
	{
		local_ci->pos = effect->pos;
		local_ci->spd = effect->velo;
		local_ci->scl = effect->scl;
		local_ci->frame = 0.0f;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->ang = 0x2000 - (int)(local_14k * 4096.0);
		local_ci->argb = effect->argb;
		local_ci->work[0].ptr = effect;
	}
}
