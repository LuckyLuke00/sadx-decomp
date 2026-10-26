#include "decls.h"

// FUNCTION: SADX 0x00855030
void DrawJumpdai(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0 && DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_DrawModelClip(*(struct NJS_MODEL **)((char *)var1->counter.ptr + 4), 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008550c0
void ExecJumpdai(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		struct OBJ_CONDITION *var2 = (struct OBJ_CONDITION *)var1->counter.ptr;
		if (var2 != 0)
		{
			*(float *)((char *)var2 + 8) = var1->pos.x;
			*(float *)((char *)var2 + 0xc) = var1->pos.y;
			*(float *)((char *)var2 + 0x10) = var1->pos.z;
			*(long *)((char *)var2 + 0x14) = var1->ang.x;
			*(long *)((char *)var2 + 0x18) = var1->ang.y;
			*(long *)((char *)var2 + 0x1c) = var1->ang.z;
			if (CheckCollisionP(&var1->pos, *(float *)((char *)var2->pTask + 0x24) + 20.0f))
			{
				var1->flag |= 0x100;
				DrawJumpdai(tp);
				return;
			}
			var1->flag &= 0xfeff;
		}
		DrawJumpdai(tp);
	}
}

// FUNCTION: SADX 0x00855160
void ObjLostWorldJumpdai(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct forcewk *var2 = tp->fwp;
	struct obj *var3;

	if (CheckRangeOut(tp) == 0)
	{
		var2->ang_spd.x = 0;
		var2->ang_spd.y = 0;
		var2->ang_spd.z = 0;
		var2->pos_spd.x = 0.0f;
		var2->pos_spd.y = 0.0f;
		var2->pos_spd.z = 0.0f;
		tp->dest = KasyaDestruct;
		tp->exec = ExecJumpdai;
		tp->disp = DrawJumpdai;
		if (FUN_004c39c0(tp) == 0)
		{
			var3 = GetMobileLandObject();
			var1->counter.ptr = var3;
			var3->scl[0] = 1.0f;
			var3->scl[1] = 1.0f;
			var3->scl[2] = 1.0f;
			var3->ang[0] = var1->ang.x;
			var3->ang[1] = var1->ang.y;
			var3->ang[2] = var1->ang.z;
			var3->pos[0] = var1->pos.x;
			var3->pos[1] = var1->pos.y;
			var3->pos[2] = var1->pos.z;
			var3->model = object_lwobj_jumpdai_jumpdai[0].model;
			var1->flag |= 0x100;
			RegisterCollisionEntry(0x40000001, tp, var3);
		}
		else
		{
			var1->counter.ptr = &object_lwobj_jumpdai_jumpdai[0];
		}
	}
}
