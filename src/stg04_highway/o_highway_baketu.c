#include "decls.h"
static void Draw(struct task *tp);

// GLOBAL: SADX 0x03e71b84
static struct CCL_INFO object_c_info[1];

static void Norm(struct task *tp);

// FUNCTION: SADX 0x00820210
static void Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	___dsDrawModel(model_ss_bkt_bkt_bkt_bkt);
	___dsDrawModel(model_ss_bkt_huta_bkt_huta);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x008205e0
static void Norm(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00820710
void ObjectHighwayBaketu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->counter.ptr = object_ss_bkt_bkt_bkt_bkt;
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
				Norm(tp);
				EntryColliList(var1);
				ObjectSetupInput(var1, 0);
			}
			Draw(tp);
			break;
		}
	}
}
