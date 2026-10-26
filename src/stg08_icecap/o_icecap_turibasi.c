#include "decls.h"
extern short DAT_05ccde90;

// FUNCTION: SADX 0x00865a00
void ObjectIcecapTuribasiExecutor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05ccde90 != 0)
	{
		BridgeEditMode(var1);
		return;
	}
	switch (var1->smode)
	{
	case 0:
		BridgeNormal(tp);
		if ((var1->cwp->flag & 1) != 0)
		{
			if (var1->cwp->hit_cwp->id == 3)
			{
				var1->smode++;
				dsPlay_oneshot(0xd2, 0, 0, 0);
				tp->disp = ObjectTuribasiDisplayer2;
			}
		}
		EntryColliList(var1);
		break;
	case 1:
		BridgeCrash(var1);
		BridgeNormal2(tp);
		var1->smode++;
		break;
	case 2:
		BridgeNormal2(tp);
		{
			int var2 = *(int *)((char *)var1 + 0x1c);
			*(int *)((char *)var1 + 0x1c) = var2 + 1;
			if (var2 > 0xc8)
			{
				var1->smode = 0;
				*(int *)((char *)var1 + 0x1c) = 0;
				return;
			}
		}
		break;
	}
}
