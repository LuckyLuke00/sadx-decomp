#include "decls.h"

// GLOBAL: SADX 0x03feb598
static struct CCL_INFO object_c_info[1];

static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x008338d0
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00833b30
void ObjectMountainLightB(struct task *tp)
{
	tp->twp->counter.ptr = object_sotolight_light_light;
	CCL_Init(tp, (struct CCL_INFO *)&object_c2_info, 1, 4);
	ObjectCCollision_setMeshNWZ(tp);
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00833b60
void ObjectMountainLight(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			if (FUN_004c39c0(tp) == 0)
			{
				CCL_Init(tp, (struct CCL_INFO *)object_c_info, 1, 4);
			}
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				EntryColliList(var1);
				ObjectSetupInput(var1, 0);
			}
			tp->twp->wtimer += 0xc;
			Draw(tp);
			break;
		}
	}
}
