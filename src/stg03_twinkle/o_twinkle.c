#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00814220
void dispTPObject(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
		}
		late_DrawObjectClipEx((struct obj *)var1->counter.ptr, 1, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008144e0
void ObjectTPBowWindow(struct task *tp)
{
	tp->twp->counter.ptr = object_mado_outmado_outmado;
	ObjectNormal_LE(tp);
}

// FUNCTION: SADX 0x00814500
void ObjectTPGirder(struct task *tp)
{
	tp->twp->counter.ptr = object_geta_cubar_cubar;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x00814630
void ObjectTPLamp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 656100.0f) == 0)
	{
		if (CheckEditMode())
		{
			var1->counter.ptr = object_tp_obj_hunger_hunger;
			dispTPLamp(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			var1->counter.ptr = object_tp_obj_hunger_hunger;
			tp->disp = dispTPLamp;
			tp->dest = destChaos7Float;
			break;
		case 1:
			dispTPLamp(tp);
			return;
		}
	}
}
