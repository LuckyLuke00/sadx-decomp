#include "decls.h"
static void ObjectWaterripple(struct task *tp);
void ObjectWaterripple(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x005708f0
void CreateWaterripple(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl)
{
	struct task *local_8g = CreateElementalTask(2, 6, ObjectWaterripple);
	struct taskwk *local_cg = local_8g->twp;

	local_cg->pos = *pos;
	local_cg->value.f = vec->x;
	local_cg->timer.f = vec->z;
	local_cg->scl.x = scl;
	local_cg->scl.y = 1.0f;
	local_cg->counter.f = -0.5f;
}

// FUNCTION: SADX 0x00570970
void ObjectWaterripple(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	*(char *)local_8 = 0;
	tp->exec = _Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
}

// FUNCTION: SADX 0x005709b0
void _Exec(struct task *tp)
{
	struct taskwk *local_10;
	float local_8g;
	float local_cj;

	local_10 = tp->twp;
	switch (local_10->mode)
	{
		case 0:
			local_8g = local_10->scl.x + local_10->value.f;
			if (local_8g > local_10->timer.f)
			{
				local_10->mode = 1;
				local_10->counter.f = -0.5;
			}
			local_10->scl.x = local_8g;
			break;
		case 1:
			local_cj = local_10->counter.f;
			local_10->scl.x += local_10->value.f;
			local_cj -= 0.019999999552965164;
			if (-1.0 > local_cj)
			{
				local_10->mode = 2;
			}
			local_10->counter.f = local_cj;
			break;
		case 2:
			FreeTask(tp);
			break;
	}
	Disp(tp);
}

// STUB: SADX 0x00570a90
static void Disp(struct task *tp)
{
}
