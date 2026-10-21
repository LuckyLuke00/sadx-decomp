#include "decls.h"

// FUNCTION: SADX 0x00866560
void ObjectHouse_a(struct task *tp)
{
	tp->twp->counter.ptr = object_obj_house_a_house_a;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x00866580
void ObjectHouse_b(struct task *tp)
{
	tp->twp->counter.ptr = object_obj_house_b_house_b;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x008665a0
void ObjectHouse_c(struct task *tp)
{
	tp->twp->counter.ptr = object_obj_house_c_house_c;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x008665c0
void ObjectHouse_d(struct task *tp)
{
	tp->twp->counter.ptr = object_obj_house_d_house_d;
	ObjectNormal(tp);
}
