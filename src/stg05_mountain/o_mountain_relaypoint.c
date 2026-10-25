#include "decls.h"

// STUB: SADX 0x00831f50
void RelaypointDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)&var1->ang.z)
		{
			njRotateZ(0, *(unsigned short *)&var1->ang.z);
		}
		if (var1->ang.x)
		{
			njRotateX(0, var1->ang.x);
		}
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		___dsAction(action_kasshatyuukei1a_st, var1->scl.x, 1.0f);
		njPopMatrix(1);
	}
}
