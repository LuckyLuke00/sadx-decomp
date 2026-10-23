#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_tpobj_slight1_slight1[1];
extern struct obj object_tpobj_slight2_slight2[1];

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

// STUB: SADX 0x008d3ec0
void ObjectTPLightI(struct task *tp)
{
}
