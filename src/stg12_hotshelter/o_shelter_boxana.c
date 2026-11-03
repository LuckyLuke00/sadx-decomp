#include "decls.h"

void FUN_0058b860(int param_1, int param_2);

// FUNCTION: SADX 0x008aed70
static void FUN_008aed70(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct obj *var2 = (struct obj *)var1->value.ptr;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_boxana_boxana_cori_boxana_cori[0].pos[0];
	var2->pos[1] = var1->pos.y + object_boxana_boxana_cori_boxana_cori[0].pos[1];
	var2->pos[2] = var1->pos.z + object_boxana_boxana_cori_boxana_cori[0].pos[2];
}

// FUNCTION: SADX 0x008aedb0
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_HotShelter2);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	late_ActionClipMesh(action_boxana_boxana, (float)*(unsigned char *)((char *)var1 + 9), 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008aee30
static void DesertATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
	ReleaseMobileLandObject((struct obj *)var1->value.ptr);
}

// FUNCTION: SADX 0x008aee60
static void FUN_008aee60(struct task *param_1)
{
	int var1;
	switch (param_1->twp->counter.b[0])
	{
	case 0:
		var1 = GetBoxSwitchOnOff(0);
		var1 &= GetBoxSwitchOnOff(1);
		var1 &= GetBoxSwitchOnOff(2);
		var1 &= GetBoxSwitchOnOff(3);
		if (var1)
		{
			FUN_0058b860(4, 1);
		}
		break;
	case 1:
		var1 = GetBoxSwitchOnOff(4);
		var1 &= GetBoxSwitchOnOff(5);
		var1 &= GetBoxSwitchOnOff(6);
		var1 &= GetBoxSwitchOnOff(7);
		if (var1)
		{
			FUN_0058b860(17, 1);
		}
		break;
	}
}

// FUNCTION: SADX 0x008aeee0
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->disp = DispATask;
	tp->dest = DesertATask;
	var1->counter.b[0] = (unsigned char)var1->scl.x;
	struct obj *var2 = GetMobileLandObject();
	var1->value.ptr = var2;
	var2->evalflags = object_boxana_boxana_cori_boxana_cori[0].evalflags;
	var2->ang[0] = 0;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_boxana_boxana_cori_boxana_cori[0].pos[0];
	var2->pos[1] = var1->pos.y + object_boxana_boxana_cori_boxana_cori[0].pos[1];
	var2->pos[2] = var1->pos.z + object_boxana_boxana_cori_boxana_cori[0].pos[2];
	var2->model = object_boxana_boxana_cori_boxana_cori[0].model;
	var2->child = 0;
	var2->sibling = 0;
	RegisterCollisionEntry(0x20000000, tp, var2);
	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->counter.b[1] = 0;
	var1->mode = 1;
}

// FUNCTION: SADX 0x008aefa0
void ObjShelterBoxAna(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 250000.0f))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		switch (var1->mode)
		{
		case 0:
			InitATask(tp);
			break;
		case 1:
			DispATask(tp);
			FUN_008aed70(tp);
			struct taskwk *var2 = tp->twp;
			var2->counter.b[1]++;
			if (var2->counter.b[1] >= action_boxana_boxana[0].motion->nbFrame)
			{
				var2->counter.b[1] = 0;
			}
			FUN_008aee60(tp);
			break;
		}
	}
	else
	{
		switch (var1->mode)
		{
		case 0:
			InitATask(tp);
			break;
		case 1:
			DebPrintf(0x110013, "-> ANA ID (0-1)");
			DispATask(tp);
			FUN_008aed70(tp);
			break;
		}
	}
}
