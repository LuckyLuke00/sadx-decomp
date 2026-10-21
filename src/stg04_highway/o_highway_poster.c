#include "decls.h"

// FUNCTION: SADX 0x00820a20
void ObjectHighwayPoster0(struct task *tp)
{
	tp->twp->counter.ptr = object_ss_poster2_poster2;
	ObjectScaleNormal(tp);
}

// FUNCTION: SADX 0x00820a40
void ObjectHighwayPoster1(struct task *tp)
{
	tp->twp->counter.ptr = object_ss_pstr_03_pstr_03;
	ObjectScaleNormal(tp);
}

// FUNCTION: SADX 0x00820a60
void ObjectHighwayPoster2(struct task *tp)
{
	tp->twp->counter.ptr = object_ss_poster4_poster4;
	ObjectScaleNormal(tp);
}
