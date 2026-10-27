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
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	SetObjectTexture();
	FUN_004a88c0((NJS_ACTION *)(*(int *)((char *)var1 + 8)), *(float *)((char *)var1 + 0xc));
	njPopMatrix(1);
	if (FUN_004c39c0(tp) == 0)
	{
		if (ChkPause() == 0)
		{
			float var2 = *(float *)((char *)var1 + 0xc) + 1.0;
			*(float *)((char *)var1 + 0xc) = var2;
			struct NJS_MOTION *var3 = *(struct NJS_MOTION **)((char *)(*(void **)((char *)var1 + 8)) + 4);
			if ((float)(unsigned int)var3->nbFrame <= var2)
			{
				*(float *)((char *)var1 + 0xc) = 0.0f;
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
