#include "decls.h"
extern struct NJS_MODEL DAT_05a7b20c;
extern struct CCL_INFO ring_colli_info[1];

// FUNCTION: SADX 0x0081d2d0
void RingDrawAct2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SaveConstantAttr();
	OffConstantAttr(0, 0x80000);
	SetRegularTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	if (*(int *)((char *)var1 + 0x14))
	{
		njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
	}
	___dsDrawModel(&DAT_05a7b20c);
	njPopMatrix(1);
	LoadConstantAttr();
}

// FUNCTION: SADX 0x0081d350
void ObjectHighwayRingAct2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 250000.0f) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			CCL_Init(tp, (struct CCL_INFO *)&ring_colli_info, 1, 7);
			var1->mode = 1;
			var1->id = 0xb;
			tp->disp = RingDrawAct2;
			break;
		case 1:
			if (CheckEditMode() == 0)
			{
				if (var1->cwp->flag & 1)
				{
					var1->mode = 2;
					AddNumRing(1);
					dsPlay_oneshot(7, 0, 0, 0);
				}
			}
			if (CheckEditMode() == 0)
			{
				EntryColliList(var1);
				var1->ang.x += 0x16c;
			}
			RingDrawAct2(tp);
			break;
		case 2:
			DeadOut(tp);
			break;
		}
	}
}
