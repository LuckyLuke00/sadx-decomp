#include "decls.h"
extern struct obj *DAT_060eeaa4;
extern struct Angle3 DAT_05ccdd40;
void FUN_007d4790(struct task *param_1);

// FUNCTION: SADX 0x007d4700
void EV_Alife_FaceChange(struct task *tp, unsigned long texid)
{
	if (tp != 0)
	{
		tp->twp->counter.l = texid;
	}
}

// FUNCTION: SADX 0x007d4720
void EVAlifeMotionCallBack(struct obj *obj)
{
	if (obj == *(struct obj **)((char *)DAT_060eeaa4 + 8))
	{
		if (DAT_05ccdd40.y != 0)
		{
			njRotateY(0, (Uint16)DAT_05ccdd40.y);
		}
		if (DAT_05ccdd40.x != 0)
		{
			njRotateX(0, (Uint16)DAT_05ccdd40.x);
		}
	}
}

// FUNCTION: SADX 0x007d49f0
void EV_Alife_cons(struct task *tp)
{
	tp->twp->counter.l = 2;
	tp->exec = EV_Alife_exec;
	tp->disp = EV_Alife_draw;
	tp->dest = FUN_007d4790;
}

// FUNCTION: SADX 0x007d4a20
struct task *EV_Alife()
{
	struct task *var1;

	var1 = CreateElementalTask(2, 3, EV_Alife_cons);
	if (var1 != NULL)
	{
		SetEventWork(var1->twp);
	}
	return var1;
}
