#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void FEGG_DrawBrokenPiece(struct taskwk *twp);

// FUNCTION: SADX 0x00898630
void ShutterPartsDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		___dsDrawModel((struct NJS_MODEL *)var1->counter.ptr);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00898800
void BrokenPieceDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		FUN_0067d2d0((float *)0, *(float *)((char *)var1 + 0x2c), *(float *)((char *)var1 + 0x2c), *(float *)((char *)var1 + 0x2c));
		FEGG_DrawBrokenPiece(var1);
		njPopMatrix(1);
	}
}
