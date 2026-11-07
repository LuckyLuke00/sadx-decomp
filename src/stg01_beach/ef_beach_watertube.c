#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// STUB: SADX 0x00803ad0
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x00803bf0
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00803db0
void ObjectBeachWatertube(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00803dd0
void CreateBeachWatertube(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl)
{
	struct task *var1 = CreateElementalTask(3, 3, ObjectBeachWatertube);
	struct taskwk *var2 = var1->twp;
	struct motionwk *var3 = var1->mwp;
	var2->pos.x = pos->x;
	var2->pos.y = pos->y;
	var2->pos.z = pos->z;
	var3->spd.x = vec->x;
	var3->spd.y = 0.0f;
	var3->spd.z = vec->z;
	var2->scl.x = 2.0f * scl;
	var2->scl.y = 0.0f;
	var2->scl.z = 0.0f;
	var2->counter.f = scl * 0.10000000149011612;
	var2->value.f = scl;
	var2->timer.f = 0.1f;
}
