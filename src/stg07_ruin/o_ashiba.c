#include "decls.h"
extern struct obj object_hebi_asibakabe02_hebi_asibakabe02_hebi_asibakabe02[];
extern struct obj object_hebi_asibakabe01_hebi_asibakabe01_hebi_asibakabe01[];
extern struct obj object_hebi_asiba03_hebi_asiba03_hebi_asiba03[];
extern struct obj object_hebi_asiba02_hebi_asiba02_hebi_asiba02[];
static void Normal(struct task *tp);
static void Exit(struct task *tp);
extern struct obj object_hebi_asiba01_hebi_asiba01_hebi_asiba01[];

// FUNCTION: SADX 0x0081f2b0
static void Exit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = (struct obj *)var1->counter.ptr;

	ReleaseMobileLandObject(var2);
	WithdrawCollisionEntry(tp, var2);
}

// STUB: SADX 0x00856f90
static void Normal(struct task *tp)
{
}

// FUNCTION: SADX 0x00857080
void ObjectAshiba01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = SetModelCollision(&object_hebi_asiba01_hebi_asiba01_hebi_asiba01[0], tp, 0x40000001);

	var1->counter.ptr = var2;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = Exit;
}

// FUNCTION: SADX 0x008570c0
void ObjectAshiba02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = SetModelCollision((struct obj *)&object_hebi_asiba02_hebi_asiba02_hebi_asiba02, tp, 0x40000001);

	var2->scl[0] = 1.0f;
	var1->counter.ptr = var2;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = Exit;
}

// FUNCTION: SADX 0x00857100
void ObjectAshiba03(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = SetModelCollision((struct obj *)&object_hebi_asiba03_hebi_asiba03_hebi_asiba03, tp, 0x40000001);
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	*(void **)((char *)var1 + 8) = var2;
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = Exit;
}

// FUNCTION: SADX 0x00857140
void ObjectAshikabe01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2;

	var2 = SetModelCollision((struct obj *)&object_hebi_asibakabe01_hebi_asibakabe01_hebi_asibakabe01, tp, 0x40000001);
	var1->counter.ptr = var2;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = Exit;
}

// FUNCTION: SADX 0x00857180
void ObjectAshikabe02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = SetModelCollision(&object_hebi_asibakabe02_hebi_asibakabe02_hebi_asibakabe02[0], tp, 0x40000001);

	var2->scl[0] = 1.0f;
	var1->counter.ptr = var2;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = Exit;
}
