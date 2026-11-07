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
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)(short)var1->ang.y);
		}
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
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
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)(short)var1->ang.y);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		FUN_0067d2d0((float *)0, var1->scl.x, var1->scl.x, var1->scl.x);
		FEGG_DrawBrokenPiece(var1);
		njPopMatrix(1);
	}
}
