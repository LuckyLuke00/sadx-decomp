#include "decls.h"
struct particle_info;
struct sp_task;
struct sp_link;
extern "C" int rand(void);

// FUNCTION: SADX 0x005538c0
void EffectFire(struct sp_task *tp, struct sp_link *lp)
{
	struct sp_link *local_cg;
	float local_8g;

	local_cg = (struct sp_link *)tp->work[0].l;
	tp->no = (short)(int)tp->frame;
	if (tp->no > 9)
	{
		tp->no = 9;
		SpFreeTask(tp);
		return;
	}
	tp->frame += *(float *)((char *)local_cg + 8);
	local_8g = *(float *)((char *)local_cg + 0xc);
	tp->spd.x = -tp->spd.x * local_8g + tp->spd.x;
	tp->spd.y = -tp->spd.y * local_8g + *(float *)((char *)local_cg + 0x10) + tp->spd.y;
	tp->spd.z = -tp->spd.z * local_8g + tp->spd.z;
	tp->pos.x += tp->spd.x;
	tp->pos.y += tp->spd.y;
	tp->pos.z += tp->spd.z;
	tp->scl += *(float *)((char *)local_cg + 4) * 0.15000000596046448;
	return;
}

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

// FUNCTION: SADX 0x00553ad0
void CreateFire2(struct particle_info *effect)
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
		local_ci->pos = effect->pos;
		local_ci->spd = effect->velo;
		local_ci->scl = effect->scl * 0.15000000596046448;
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
