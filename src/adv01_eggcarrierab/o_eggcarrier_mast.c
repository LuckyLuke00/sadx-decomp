#include "decls.h"
extern int DAT_05b9d838;
extern struct obj **DAT_060eea88;
void FUN_00825de0(struct task *param_1);

// FUNCTION: SADX 0x00694a70
static void DrawMast(struct taskwk *twp)
{
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		if (((struct obj *)twp->counter.ptr)->ang[1] != 0)
		{
			njRotateY(0, (Uint16)((struct obj *)twp->counter.ptr)->ang[1]);
		}
		ds_DrawObjectClip(DAT_060eea88[0x22], 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00694ad0
void MastDisplayer(struct task *tp)
{
	DrawMast(tp->twp);
}

// FUNCTION: SADX 0x00694ae0
void ObjectECMast(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 local_14;
	struct obj *var2;
	struct forcewk *var3;

	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->timer.ptr = DAT_060eea88[0x23];
			var2 = GetMobileLandObject();
			var1->counter.ptr = var2;
			var2->scl[0] = 1.0f;
			var2->scl[1] = 1.0f;
			var2->scl[2] = 1.0f;
			var2->evalflags = 0x10;
			var2->ang[0] = 0;
			var2->ang[1] = 0;
			var2->ang[2] = 0;
			var2->pos[0] = var1->pos.x;
			var2->pos[1] = var1->pos.y;
			var2->pos[2] = var1->pos.z;
			var2->model = ((struct obj *)var1->timer.ptr)->model;
			var2->child = 0;
			var2->sibling = 0;
			RegisterCollisionEntry(0x8000001, tp, var2);
			tp->dest = FUN_00825de0;
			tp->disp = MastDisplayer;
			var1->mode = 1;
			break;
		case 1:
			var3 = tp->fwp;
			var1->ang.y += 0x80;
			((struct obj *)var1->counter.ptr)->ang[1] = var1->ang.y;
			var3->ang_spd.y = 0x80;
			local_14 = DAT_05baf368[0]->pos;
			njSubVector(&local_14, &var1->pos);
			local_14.y = 0.0f;
			local_14.x = njScalor(&local_14) * njTan(0x80);
			local_14.y = 0.0f;
			local_14.z = 0.05f;
			njPushMatrix(&_nj_unit_matrix_);
			if (var1->ang.y - 0x80 != 0)
			{
				njRotateY(0, (Uint16)(var1->ang.y - 0x80));
			}
			njCalcVector(0, &local_14, &local_14);
			njPopMatrix(1);
			var3->pos_spd = local_14;
			break;
		}
		var1->flag &= 0xFEFF;
		if (njSqrt((DAT_05baf368[0]->pos.x - var1->pos.x) * (DAT_05baf368[0]->pos.x - var1->pos.x) + (DAT_05baf368[0]->pos.y - var1->pos.y) * (DAT_05baf368[0]->pos.y - var1->pos.y) + (DAT_05baf368[0]->pos.z - var1->pos.z) * (DAT_05baf368[0]->pos.z - var1->pos.z)) < 200.0)
		{
			var1->flag |= 0x100;
		}
		DrawMast(tp->twp);
	}
}
