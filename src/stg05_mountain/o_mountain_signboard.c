#include "decls.h"

// FUNCTION: SADX 0x00831e40
void ObjectMountainSignboardDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, (unsigned short)*(short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		ds_DrawObjectClip(object_danger01_danger1a_danger1a, 1.0f);
		njPopMatrix(1);
	}
}
