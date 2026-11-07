#include "decls.h"
extern struct NJS_ACTION action_skymain_eskwa_u[1];

// FUNCTION: SADX 0x00701f50
void exitSkyEscalatorManager(struct task *tp)
{
	FreeTaskC(tp);
	FreeTask(tp);
}

// FUNCTION: SADX 0x00841230
void dispSkyEscalator(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	SetObjectTexture();
	FUN_004a88c0((NJS_ACTION *)((int)var1->counter.l), var1->timer.f);
	njPopMatrix(1);
	if (FUN_004c39c0(tp) == 0)
	{
		if (ChkPause() == 0)
		{
			float var2 = var1->timer.f + 1.0;
			var1->timer.f = var2;
			struct NJS_MOTION *var3 = *(struct NJS_MOTION **)((char *)(var1->counter.ptr) + 4);
			if ((float)(unsigned int)var3->nbFrame <= var2)
			{
				var1->timer.f = 0.0f;
			}
		}
	}
}

// FUNCTION: SADX 0x008412d0
void execSkyEscalator(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
		case 0:
			var1->mode = 1;
			var1->counter.ptr = &action_skymain_eskwa_u;
			tp->dest = destChaos7Float;
			tp->disp = dispSkyEscalator;
			break;
		case 1:
			dispSkyEscalator(tp);
			break;
	}
}
