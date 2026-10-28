#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
extern struct particle_entry particle_water;
extern "C" int rand(void);

// FUNCTION: SADX 0x00571790
void EffectWater(sp_task *tp, sp_link *lp)
{
	void *local_cg;
	float local_8g;

	local_cg = tp->work[0].ptr;
	tp->no = (short)((long)(tp->frame));
	if (tp->no > 7)
	{
		tp->no = 7;
		SpFreeTask(tp);
	}
	else
	{
		if (6.0 > tp->frame)
		{
			tp->frame = ((float *)local_cg)[2] * 1.399999976158142f + tp->frame;
		}
		else
		{
			tp->frame = ((float *)local_cg)[2] * 2.799999952316284f + tp->frame;
		}
		local_8g = 1.0 - ((float *)local_cg)[3];
		tp->spd.x = tp->spd.x * local_8g;
		tp->spd.y = tp->spd.y * local_8g + ((float *)local_cg)[4];
		tp->spd.z = tp->spd.z * local_8g;
		tp->pos.x = tp->pos.x + tp->spd.x;
		tp->pos.y = tp->pos.y + tp->spd.y;
		tp->pos.z = tp->pos.z + tp->spd.z;
		tp->scl = ((float *)local_cg)[1] * 0.17000000178813934f * 1.5f + tp->scl;
	}
}

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
