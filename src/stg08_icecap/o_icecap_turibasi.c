#include "decls.h"

// GLOBAL: SADX 0x045da780
static struct CCL_INFO hasi_colli_info[1];

extern struct bridge_model_info icecap_bridge_01;
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
			int var2 = var1->ang.z;
			var1->ang.z = var2 + 1;
			if (var2 > 0xc8)
			{
				var1->smode = 0;
				var1->ang.z = 0;
				return;
			}
		}
		break;
	}
}

// FUNCTION: SADX 0x00865ac0
void ObjectIcecapTuribasi1(struct task *tp)
{
	tp->twp->value.ptr = &icecap_bridge_01;
	CCL_Init(tp, hasi_colli_info, 1, 4);
	tp->twp->cwp->colli_range = 500.0f;
	ObjectTuribasi(tp);
	tp->exec = ObjectIcecapTuribasiExecutor;
}
