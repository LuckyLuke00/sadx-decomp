#include "decls.h"
void FUN_007d21b0(...);

// FUNCTION: SADX 0x00835ed0
void Object_Mountain_Kumonosu_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (var1->ang.x != 0)
		{
			njRotateX(0, (Uint16)var1->ang.x);
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
		}
		FUN_0067d2d0(0, var1->scl.x, var1->scl.y, var1->scl.z);
		ds_DrawModelClip((struct NJS_MODEL *)(*(int *)((char *)&object_kumonosu_kumonosu1a_kumonosu1a + 4)), FUN_004a1e90(&var1->scl.x));
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00835fa0
void Object_Mountain_Kumonosu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp))
		{
			var1->timer.l = (long)&object_kumonosu_kumonosu1a_kumonosu1a;
			var1->value.l = (long)&texlist_obj_mountain;
			return;
		}
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			var1->timer.l = (long)&object_kumonosu_kumonosu1a_kumonosu1a;
			var1->value.l = (long)&texlist_obj_mountain;
			tp->disp = Object_Mountain_Kumonosu_Display;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			break;
		case 1:
			Object_Mountain_Kumonosu_Display(tp);
			return;
		}
	}
}
