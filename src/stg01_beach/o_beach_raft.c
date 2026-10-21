#include "decls.h"

// FUNCTION: SADX 0x007f99e0
void ObjectBeachFloot(struct task *tp)
{
	tp->twp->timer.ptr = object_seaobj_floot_floot;
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x007f9a00
void ObjectBeachBungalow(struct task *tp)
{
	tp->twp->timer.ptr = object_seaobj_bungalow_bungalow;
	ObjectCCollision_setMeshWZ(tp);
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x007f9a20
void ObjectBeachRock(struct task *tp)
{
	tp->twp->timer.ptr = object_seaobj_rock_rock;
	ObjectCCollision_setWZ(tp);
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x007f9a40
void ObjectBeachIwapole(struct task *tp)
{
	tp->twp->timer.ptr = object_seaobj_iwapole_iwapole;
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x007f9a60
void ObjectBeachSekityu(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_sekichuu_sekichuu;
	if (!FUN_004c39c0(tp) && tp->twp && !tp->twp->cwp)
	{
		CCL_Init(tp, object_seki_info, 1, 4);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x007f9ab0
void ObjectBeachKomorebi(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_komorebi_komorebi;
	ObjectScaleNormal(tp);
}

// FUNCTION: SADX 0x007f9ad0
void ObjectBeachRock2(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_rock2_rock2;
	if (!FUN_004c39c0(tp) && tp->twp && !tp->twp->cwp)
	{
		CCL_Init(tp, object_seki_info + 1, 1, 4);
	}
	ObjectCCollision(tp);
}
