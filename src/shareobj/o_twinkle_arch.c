#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;
extern int DAT_05b9d838;
extern struct obj object_tpobj_slight1_slight1[1];
extern struct obj object_tpobj_slight2_slight2[1];

// STUB: SADX 0x008d31f0
void ObjectTPArchI(struct task *tp)
{
}

// FUNCTION: SADX 0x008d3370
void dispTPArch(struct task *tp)
{
	struct taskwk *local_8g;

	local_8g = tp->twp;
	if (DAT_05b9d838 != 0)
		return;
	___njSetTexture(&texlist_obj_shareobj);
	njPushMatrix(0);
	njTranslateV(0, &local_8g->pos);
	if (local_8g->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8g->ang.z);
	if (local_8g->ang.x != 0)
		njRotateX(0, local_8g->ang.x);
	if (local_8g->ang.y != 0)
		njRotateY(0, local_8g->ang.y);
	if ((local_8g->counter.ptr == &object_tpobj_slight1_slight1[0]) || (local_8g->counter.ptr == &object_tpobj_slight2_slight2[0]))
		late_DrawObjectEx((struct obj *)local_8g->counter.ptr, 0);
	else
		___dsDrawObject((struct obj *)local_8g->counter.ptr);
	njPopMatrix(1);
}

// STUB: SADX 0x008d3450
void dispTPArchI(struct task *tp)
{
}

// STUB: SADX 0x008d3560
void execTPArchIISub(struct task *tp)
{
}

// STUB: SADX 0x008d36b0
void dispTPArchIISub(struct task *tp)
{
}

// STUB: SADX 0x008d3db0
void dispTPArchII(struct task *tp)
{
}

// FUNCTION: SADX 0x008d3ec0
void ObjectTPLightI(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (CheckRangeOutWithR(tp, 9060100.0f) != 0)
		return;
	if (((DAT_05b9d724 << 8) | DAT_05b9d744) != 0x300)
	{
		if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) != 0x2300)
			return;
	}
	if (CheckEditMode() != 0)
	{
		local_8->counter.ptr = &object_tpobj_slight1_slight1[0];
		dispTPArch(tp);
		return;
	}
	switch (local_8->mode)
	{
		case 0:
			local_8->mode = 1;
			local_8->counter.ptr = &object_tpobj_slight1_slight1[0];
			tp->disp = dispTPArch;
			tp->dest = FUN_0049e8b0;
			break;
		case 1:
			dispTPArch(tp);
			break;
	}
}

// STUB: SADX 0x008d3fa0
void ObjectTPLightII(struct task *tp)
{
}
