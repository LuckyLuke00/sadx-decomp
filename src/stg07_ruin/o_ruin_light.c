#include "decls.h"

// FUNCTION: SADX 0x00853c00
void ObjectRuinLight(struct task *tp)
{
	tp->twp->counter.ptr = object_lwobj_komorebi2_komorebi2;
	ObjectCCollision_setNWZ(tp);
	ObjectScaleNormal(tp);
}

// FUNCTION: SADX 0x00853d90
void ObjectRuinLightEff(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		var1->timer.f = 1.0;
		tp->disp = dispObjectRuinLightEff;
		break;
	case 1:
		var1->counter.f = *(float *)((char *)var1 + 0x30) + 0.019999999552965164 + var1->counter.f;
		var1->timer.f = var1->timer.f - 0.029999999329447746;
		dispObjectRuinLightEff(tp);
		if (var1->timer.f <= -1.0)
		{
			var1->mode = 2;
			return;
		}
		break;
	case 2:
		FreeTask(tp);
		return;
	}
}
