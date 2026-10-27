#include "decls.h"
extern struct CCL_INFO DAT_03b75728[];

// FUNCTION: SADX 0x00808dd0
void ObjectWindyUkisima(struct task *tp)
{
	tp->twp->counter.ptr = object_wvobj_ukisima_ukisima;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, object_uki_info, 2, 4);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00808e10
void ObjectWindyBigFloot(struct task *tp)
{
	tp->twp->timer.ptr = object_windobj_bigfloot_bigfloot;
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x00808e70
void ObjectWindyTateiwaS(struct task *tp)
{
	tp->twp->counter.ptr = object_wvobj_tateiwa_s_tateiwa_s;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, DAT_03b75728, 1, 4);
	}
	ObjectCCollision_setWZ(tp);
	ObjectCCollision(tp);
}
