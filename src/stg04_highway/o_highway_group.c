#include "decls.h"

// FUNCTION: SADX 0x0081d180
void ObjectHighwayGroupFF(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x820d90;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = (void (*)(struct task *))0x81cc10;
}

// FUNCTION: SADX 0x0081d210
void ObjectHighwayGroupGreenA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81ead0;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = (void (*)(struct task *))0x81cc10;
}

// FUNCTION: SADX 0x0081d240
void ObjectHighwayGroupGreenB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = (long)ObjectHighwayGreenB;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = (void (*)(struct task *))0x81cc10;
}
