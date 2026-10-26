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

// FUNCTION: SADX 0x00807e60
void ObjectWindyTuriBroken(struct task *tp)
{
	tp->twp->value.ptr = &windy_bridge_01;
	CCL_Init(tp, hasi_colli_info, 1, 4);
	tp->twp->cwp->colli_range = 500.0f;
	ObjectTuribasi(tp);
	tp->exec = ObjectWindyTuribasiExecutor;
}

// FUNCTION: SADX 0x00807ea0
void ObjectWindyTuriBroken2(struct task *tp)
{
	tp->twp->value.ptr = &windy_bridge_02;
	CCL_Init(tp, hasi_colli_info2, 3, 4);
	tp->twp->cwp->colli_range = 500.0f;
	ObjectTuribasi(tp);
	tp->exec = ObjectWindyTuribasiExecutor;
}

// STUB: SADX 0x00807ee0
void ObjectWindyTuriBrokenE102(struct task *tp)
{
}
