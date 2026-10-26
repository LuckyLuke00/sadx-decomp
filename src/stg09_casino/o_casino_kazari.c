#include "decls.h"

// STUB: SADX 0x0087a570
void KazariDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x0087a9a0
void KazariADisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		if (dsCheckViewV(&var1->pos, 98.0f))
		{
			SetObjectTexture2(0xc);
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (var1->ang.y)
			{
				njRotateY(0, var1->ang.y);
			}
			FUN_004a88c0(action_csn_ura_kzaa, var1->value.f);
			njPopMatrix(1);
		}
	}
}

// FUNCTION: SADX 0x0087ac10
void ObjectCasinoKazariA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &coll_0[0], 4, 4);
		}
		var1->value.f = var1->scl.x;
		tp->disp = KazariADisp;
		tp->exec = kazariAExec;
	}
}

// STUB: SADX 0x0087adc0
void ObjectCasinoKazariE(struct task *tp)
{
}

// STUB: SADX 0x0087ae30
void ObjectCasinoKazariF(struct task *tp)
{
}
