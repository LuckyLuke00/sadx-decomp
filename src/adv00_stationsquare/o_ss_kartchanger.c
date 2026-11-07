#include "decls.h"
static void Exec(struct task *tp);
void FUN_007d21b0(...);

// STUB: SADX 0x00685a60
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00685bd0
void ObjectSSKartchanger(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->exec = Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var1->counter.f = (var1->scl.x + 1.0f) * 5.0f;
	var1->timer.f = (var1->scl.y + 1.0f) * 5.0f;
	var1->value.f = (var1->scl.z + 1.0f) * 5.0f;
}
