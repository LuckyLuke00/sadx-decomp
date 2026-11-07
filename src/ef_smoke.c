#include "decls.h"

// GLOBAL: SADX 0x025dec38
static struct particle_info default_smoke;

struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
void EffectSmoke(struct sp_task *tp, struct sp_link *lp);
extern "C" int rand(void);

// FUNCTION: SADX 0x005533c0
void EffectSmokeExp(struct sp_task *tp, struct sp_link *lp)
{
	tp->no = (short)(int)tp->frame;
	if (tp->no >= *(short *)((char *)*(int *)((char *)lp + 0x10) + 8))
	{
		tp->no = *(short *)((char *)*(int *)((char *)lp + 0x10) + 8) - 1;
		SpFreeTask(tp);
		return;
	}
	if (tp->frame < 6.0)
	{
		tp->frame += 0.1899999976158142;
	}
	else
	{
		tp->frame += 0.5699999928474426;
	}
	tp->scl += 0.00570000009611249;
	tp->pos.y += 0.30000001192092896;
	tp->pos.z += 0.10000000149011612;
	return;
}

// FUNCTION: SADX 0x00553480
void EffectSmoke(struct sp_task *tp, struct sp_link *lp)
{
	struct sp_link *local_cg;
	float local_8g;

	local_cg = (struct sp_link *)tp->work[0].l;
	tp->no = (short)(int)tp->frame;
	if (tp->no >= *(short *)((char *)*(int *)((char *)lp + 0x10) + 8))
	{
		tp->no = *(short *)((char *)*(int *)((char *)lp + 0x10) + 8) - 1;
		SpFreeTask(tp);
		return;
	}
	if (tp->frame < 6.0)
	{
		tp->frame += *(float *)((char *)local_cg + 8);
	}
	else
	{
		tp->frame = *(float *)((char *)local_cg + 8) * 2.0 + tp->frame;
	}
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

// FUNCTION: SADX 0x005537c0
void CreateAddSmoke(struct particle_info *effect)
{
	struct sp_link *local_8gk;
	struct sp_task *local_ci;
	int local_10hk;
	float local_14k;
	int local_18go;
	float local_1co;

	local_8gk = particle_addsmoke.link;
	local_ci = SpCreateTask(local_8gk, EffectSmoke);
	if (local_ci != NULL)
	{
		local_ci->pos = effect->pos;
		local_ci->spd = effect->velo;
		local_ci->scl = effect->scl * 0.15000000596046448;
		local_10hk = rand();
		local_14k = (float)(local_10hk / 32768.0);
		local_ci->frame = (float)(local_14k * 6.0);
		local_18go = rand();
		local_1co = (float)(local_18go / 32768.0);
		local_ci->ang = (int)((local_1co * 360.0) * 65536.0 / 360.0);
		local_ci->argb = effect->argb;
		local_ci->work[0].ptr = effect;
	}
}
