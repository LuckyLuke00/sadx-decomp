#include "decls.h"
extern unsigned char DAT_060dbca1;
static void Exit(struct task *tp);

// GLOBAL: SADX 0x0480d240
static struct CCL_INFO object_c_info[4];

static void Normal2(struct task *tp);

// FUNCTION: SADX 0x00883c50
static void Exit(struct task *tp)
{
	if (tp->twp->mode == 0)
	{
		FreeTaskC(tp);
	}
}

// FUNCTION: SADX 0x00883da0
void cNormal1(struct task *ctp)
{
	struct taskwk *var1 = ctp->twp;
	struct colliwk *var2 = var1->cwp;
	struct taskwk *var3 = ctp->ptp->twp;
	if ((var2->flag & 1) != 0)
	{
		if ((var1->flag & 0x8000) == 0)
		{
			switch (var1->btimer)
			{
				case 0:
					var3->flag |= 0x100;
					if ((DAT_060dbcb0 & 0x400000) != 0)
					{
						if (DAT_060dbca1 >= 3)
						{
							DAT_060dbcb0 |= 0x1800;
							DAT_060dbca1++;
							SetGetRing((unsigned char)(DAT_060dbca1 - 2) ^ 0x50);
						}
					}
					break;
				case 1:
					var3->flag |= 0x200;
					break;
				case 2:
					var3->flag |= 0x400;
					break;
			}
			SetGetRing(1);
			var1->flag |= 0x8000;
		}
	}
	else
	{
		var1->flag &= 0x7fff;
	}
	EntryColliList(var1);
	ObjectSetupInput(var1, 0);
}

// STUB: SADX 0x00883fe0
static void Normal2(struct task *tp)
{
}

// FUNCTION: SADX 0x008841a0
void ObjectRightLane(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 1;
	var1->btimer = 0;
	CCL_Init(tp, &object_c_info[3], 1, 4);
	tp->exec = Normal2;
	tp->dest = Exit;
}
