#include "decls.h"
static void KumoInit(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x007efec0
void KumoInit(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007f0100
void EffectKumo(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
		case 0:
			KumoInit(tp);
			break;
		case 1:
			KumoAnimation(tp);
			break;
		case 2:
			DestroyTask(tp);
			break;
	}
}
