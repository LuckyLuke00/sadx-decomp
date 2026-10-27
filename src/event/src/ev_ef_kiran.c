#include "decls.h"
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *));
extern struct particle_entry particle_kiran;
extern "C" int rand(void);
void ev_effectKiran2(struct sp_task *tp, struct sp_link *lp);

// FUNCTION: SADX 0x007d8840
void ev_effectKiran2(struct sp_task *tp, struct sp_link *lp)
{
	short var1;

	tp->no = (short)((long)(tp->frame));
	var1 = (short)lp->info->animnum;
	if (tp->no >= var1)
	{
		tp->no = var1 - 1;
		SpFreeTask(tp);
		return;
	}
	tp->ang += tp->work[0].l;
	tp->frame = tp->frame + 0.01f;
	tp->spd.x = tp->spd.x * 1.02f;
	tp->spd.y = tp->spd.y * 0.98f;
	tp->spd.z = tp->spd.z * 1.02f;
	tp->pos.x = tp->pos.x + tp->spd.x;
	tp->pos.y = tp->pos.y + tp->spd.y;
	tp->pos.z = tp->pos.z + tp->spd.z;
	tp->scl = tp->work[1].f * tp->scl;
}

// FUNCTION: SADX 0x007d88f0
void EvCreateKiran2(struct NJS_POINT3 *pos, struct NJS_POINT3 *velo, float scl, float scl_spd)
{
	struct sp_task *local_8;
	float local_c;
	local_8 = SpCreateTask(particle_kiran.link, ev_effectKiran2);
	if (local_8)
	{
		local_8->pos = *pos;
		local_8->spd = *velo;
		local_8->scl = scl;
		local_8->frame = 0.0f;
		local_c = (float)rand() * 3.0517578125e-05;
		local_8->ang = (long)(local_c * 360.0 * 65536.0 / 360.0);
		local_8->argb.a = 1.0f;
		local_8->argb.r = 1.0f;
		local_8->argb.g = 1.0f;
		local_8->argb.b = 1.0f;
		local_c = (float)rand() * 3.0517578125e-05;
		local_8->work[0].l = (long)(local_c * 910.0 - 455.0);
		local_8->work[1].f = scl_spd;
	}
}
