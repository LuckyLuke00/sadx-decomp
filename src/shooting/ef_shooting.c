#include "decls.h"

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
