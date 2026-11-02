#include "decls.h"
static struct CCL_INFO ColliInfo[1];

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

// FUNCTION: SADX 0x00831ef0
void ObjectMountainSignboard(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			tp->disp = ObjectMountainSignboardDisp;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			CCL_Init(tp, &ColliInfo[0], 1, 4);
			break;
		case 1:
			ObjectMountainSignboardDisp(tp);
			EntryColliList(var1);
			break;
		}
	}
}
