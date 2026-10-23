#include "decls.h"
extern struct bridge_model_info mountain_bridge_04;
extern struct bridge_model_info mountain_bridge_02;
void ObjectTuribasi(struct task *tp);

// FUNCTION: SADX 0x0082eef0
void ObjectMountainTuribasi1(struct task *tp)
{
	tp->twp->value.ptr = &mountain_bridge_01;
	ObjectTuribasi(tp);
}

// FUNCTION: SADX 0x0082ef10
void ObjectMountainTuribasi2(struct task *tp)
{
	tp->twp->value.ptr = &mountain_bridge_02;
	ObjectTuribasi(tp);
}

// FUNCTION: SADX 0x0082ef30
void ObjectMountainTuribasi3(struct task *tp)
{
	tp->twp->value.ptr = &mountain_bridge_03;
	ObjectTuribasi(tp);
}

// FUNCTION: SADX 0x0082ef50
void ObjectMountainTuribasi4(struct task *tp)
{
	tp->twp->value.ptr = &mountain_bridge_04;
	ObjectTuribasi(tp);
}
