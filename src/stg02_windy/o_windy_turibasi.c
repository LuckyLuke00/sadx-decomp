#include "decls.h"
extern struct bridge_model_info windy_bridge_01;

// FUNCTION: SADX 0x00807560
void ObjectWindyTuribasi1(struct task *tp)
{
	tp->twp->value.ptr = &windy_bridge_01;
	ObjectTuribasi(tp);
}

// FUNCTION: SADX 0x00807580
void ObjectWindyTuribasiDisplayer(struct task *tp)
{
	ObjectTuribasiDisplayer(tp);
	ObjectTuribasiDisplayer2(tp);
}

// FUNCTION: SADX 0x008078d0
void ObjectWindyStoneBridge(struct task *tp)
{
	tp->twp->timer.ptr = object_windobj_isibasi_isibasi;
	ObjectGCollision(tp);
}

// STUB: SADX 0x00807ee0
void ObjectWindyTuriBrokenE102(struct task *tp)
{
}
