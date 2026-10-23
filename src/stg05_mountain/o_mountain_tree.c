#include "decls.h"
extern struct obj object_ki01_ki01_ki01[1];

// FUNCTION: SADX 0x0082e690
void Disp01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		if (FUN_004c39c0(tp))
		{
			FUN_0067d2d0(0, var1->scl.x + 1.0f, var1->scl.y + 1.0f, var1->scl.z + 1.0f);
		}
		else
		{
			FUN_0067d2d0(0, var1->scl.x, var1->scl.y, var1->scl.z);
		}
		ds_DrawModelClip(object_ki01_ki01_ki01[0].model, FUN_004a1e90((float *)&var1->scl));
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0082e890
void Exec01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
	Disp01(tp);
}

// FUNCTION: SADX 0x0082e8d0
void Exec02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
	Disp02(tp);
}
