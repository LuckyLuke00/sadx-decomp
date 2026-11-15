#include "decls.h"

// FOLD: the game's link folded this copy into the one of o_finalegg_roboshutter.c (0x00898800).
static void BrokenPieceDisplayer(struct task *tp)
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

extern int DAT_05b9d838;
extern struct obj object_dramcan_can_can;

// FUNCTION: SADX 0x00897b70
void DrumPartsDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		___dsDrawModel((struct NJS_MODEL *)var1->counter.ptr);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00897bf0
void EffectBomb(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x00897eb0
void DrumDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawObjectClip(&object_dramcan_can_can, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00898010
void BrokenPiece(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;
	switch (var1->mode)
	{
	case 0:
		FEGG_SetDynamicsWork(tp, 0);
		tp->disp = BrokenPieceDisplayer;
		var1->mode = 1;
		break;
	case 1:
		if (var1->flag & 1)
		{
			var1->btimer++;
			if (var1->btimer == 4)
			{
				var2->ang_spd.z = 0;
				var1->mode = 2;
				break;
			}
			FEGG_TaskActBounce(var1, var2);
			var2->ang_spd.z *= UNKNOWN_DOUBLE_MACRO(0.6f);
		}
		FEGG_TaskActGravity(var1, var2);
		FEGG_TaskMove(var1, var2);
		var1->ang.z += var2->ang_spd.z;
		break;
	}
	FEGG_TaskCheckGround(var1, var2);
	BrokenPieceDisplayer(tp);
}
