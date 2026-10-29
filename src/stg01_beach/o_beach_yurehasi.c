#include "decls.h"
extern struct obj object_col_hasi_a_hasi_a[2];
extern struct CCL_INFO hasi_a0_info[1];
extern struct CCL_INFO hasi_a1_info[1];
extern float DAT_060cedec[4];
extern int DAT_05b9d838;
extern struct obj object_seaobj_hasi_b_hasi_b[];
extern struct task *DAT_060cee5c;

// FUNCTION: SADX 0x00802290
void DestructYurehasi(void)
{
	if (DAT_060cee5c != NULL)
	{
		FreeTask(DAT_060cee5c);
	}
}

// FUNCTION: SADX 0x00802400
void A_Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	if (var1->smode)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	___dsDrawObject((struct obj *)var1->value.ptr);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00802460
void B_Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		if (var1->smode == 0)
		{
			SetObjectTexture();
			njPushMatrix(0);
			njTranslateV(0, &var1->pos);
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
			}
			if (*(int *)((char *)var1 + 0x1c) != 0)
			{
				njRotateX(0, *(unsigned short *)((char *)var1 + 0x1c));
			}
			ds_DrawObjectClip(object_seaobj_hasi_b_hasi_b, 1.0f);
			njPopMatrix(1);
		}
	}
}

// FUNCTION: SADX 0x008028c0
void A_Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	A_Disp(tp);
	{
		float var2 = DAT_060cedec[var1->btimer];
		var1->pos.y = var2;
		*(float *)((char *)var1->counter.ptr + 0xc) = var2;
	}
	EntryColliList(var1);
}

// STUB: SADX 0x00802900
void B_Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x00802950
void A_Init(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct forcewk *var2 = tp->fwp;
	struct obj *var3;

	var1->smode = 0;
	var2->pos_spd.x = 0.0f;
	var2->pos_spd.y = 0.0f;
	var2->pos_spd.z = 0.0f;
	var2->ang_spd.x = 0;
	var2->ang_spd.y = 0;
	var2->ang_spd.z = 0;
	var3 = GetMobileLandObject();
	var1->counter.ptr = var3;
	var3->scl[0] = 1.0f;
	var3->scl[1] = 1.0f;
	var3->scl[2] = 1.0f;
	var3->evalflags = 0x10;
	var3->ang[0] = 0;
	var3->ang[1] = var1->ang.y;
	var3->ang[2] = 0;
	var3->pos[0] = var1->pos.x;
	var3->pos[1] = var1->pos.y;
	var3->pos[2] = var1->pos.z;
	var3->model = object_col_hasi_a_hasi_a[0].model;
	var3->child = 0;
	var3->sibling = 0;
	RegisterCollisionEntry(0x68000001, tp, var3);
	var1->flag |= 0x100;
	if (var1->btimer == 0)
	{
		CCL_Init(tp, hasi_a0_info, 4, 4);
	}
	else
	{
		CCL_Init(tp, hasi_a1_info, 4, 4);
	}
	SET_COLLI_RANGE(var1->cwp, 80.0f);
	tp->exec = A_Exec;
	tp->disp = A_Disp;
	tp->dest = FUN_00825de0;
}

// STUB: SADX 0x00802a30
void B_Init(struct task *tp)
{
}

// FUNCTION: SADX 0x00802bf0
void CreateYurehasi(void)
{
	struct task *var1 = CreateElementalTask(2, 3, ObjectBeachYurehasi);
	DAT_060cee5c = var1;
	struct taskwk *var2 = var1->twp;
	var2->pos.x = 2803.0f;
	var2->pos.y = -1.0f;
	var2->pos.z = 365.0f;
}
