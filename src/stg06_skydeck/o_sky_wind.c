#include "decls.h"
void FUN_007d21b0(void *param_1);

// STUB: SADX 0x0083edf0
void ObjectSkydeck_vent_Draw(struct task *tp)
{
}

// STUB: SADX 0x0083efe0
void ObjectSkydeck_signal_Draw(struct task *tp)
{
}

// FUNCTION: SADX 0x0083f4b0
void ObjectSkydeck_decal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		if (var1->mode == 1)
		{
			if (SkydeckCheck_break(var1->pos.x, var1->pos.y, var1->pos.z) == 0)
			{
				return;
			}
			DeadOut(tp);
			return;
		}
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		tp->disp = ObjectSkydeck_decal_Draw;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		break;
	case 1:
		if (SkydeckCheck_break(var1->pos.x, var1->pos.y, var1->pos.z) == 0)
		{
			break;
		}
		*(int *)((char *)var1 + 0x1c) += -256;
		var1->pos.y += 3.4000000953674316;
		var1->pos.x += 3.5;
		break;
	}
	ObjectSkydeck_decal_Draw(tp);
}

// STUB: SADX 0x0083f580
void ObjectSkydeck_signal(struct task *tp)
{
}
