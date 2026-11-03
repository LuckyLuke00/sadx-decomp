#include "decls.h"
#include <stdlib.h>

// GLOBAL: SADX 0x04ad84d8
static struct particle_info shutter_smoke;

// The game's link folded this copy into the one of o_shelter_boxana.c (0x008aee30).
static void DesertATask(struct task *tp)
{
	struct taskwk *twp = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)twp->value.ptr);
	ReleaseMobileLandObject((struct obj *)twp->value.ptr);
}
// The game's link folded this copy into the one of o_shelter_grass.c (0x008b0910).
static void BrokenPieceDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_HotShelter0);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, (unsigned short)*(short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		FUN_0067d2d0(0, *(float *)((char *)var1 + 0x2c), *(float *)((char *)var1 + 0x2c), *(float *)((char *)var1 + 0x2c));
		FEGG_DrawBrokenPiece(var1);
		njPopMatrix(1);
	}
}

// The game's link folded this copy into the one of o_shelter_grass.c (0x008b0ca0).
static void ShutterBrokenPiece(struct task *tp)
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
			var2->ang_spd.z *= (double)0.6f;
		}
		FEGG_TaskActGravity(var1, var2);
		FEGG_TaskMove(var1, var2);
		var1->ang.z += var2->ang_spd.z;
		break;
	}
	FEGG_TaskCheckGround(var1, var2);
	BrokenPieceDisplayer(tp);
}

// FUNCTION: SADX 0x008b12a0
static void InitBTask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
	ReleaseMobileLandObject((struct obj *)var1->value.ptr);
	struct obj *var2 = GetMobileLandObject();
	var1->value.ptr = var2;
	var2->evalflags = object_breakkabe_aftercoli_aftercoli[0].evalflags;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_breakkabe_aftercoli_aftercoli[0].pos[0];
	var2->pos[1] = var1->pos.y + object_breakkabe_aftercoli_aftercoli[0].pos[1];
	var2->pos[2] = var1->pos.z + object_breakkabe_aftercoli_aftercoli[0].pos[2];
	var2->model = object_breakkabe_aftercoli_aftercoli[0].model;
	var2->child = 0;
	var2->sibling = 0;
	RegisterCollisionEntry(0x20000000, tp, var2);
}

// FUNCTION: SADX 0x008b1330
static void ExecATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckCollisionP(&var1->pos, 148.0f))
	{
		var1->flag |= 0x100;
	}
	else
	{
		var1->flag &= ~0x100;
	}
	struct obj *var2 = (struct obj *)var1->value.ptr;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_breakkabe_beforecoli_beforecoli[0].pos[0];
	var2->pos[1] = var1->pos.y + object_breakkabe_beforecoli_beforecoli[0].pos[1];
	var2->pos[2] = var1->pos.z + object_breakkabe_beforecoli_beforecoli[0].pos[2];
	var2->model = object_breakkabe_beforecoli_beforecoli[0].model;
	var2->child = 0;
	var2->sibling = 0;
}

// FUNCTION: SADX 0x008b13b0
static void FUN_008b13b0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct obj *var2 = (struct obj *)var1->value.ptr;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_breakkabe_aftercoli_aftercoli[0].pos[0];
	var2->pos[1] = var1->pos.y + object_breakkabe_aftercoli_aftercoli[0].pos[1];
	var2->pos[2] = var1->pos.z + object_breakkabe_aftercoli_aftercoli[0].pos[2];
	var2->model = object_breakkabe_aftercoli_aftercoli[0].model;
	var2->child = 0;
	var2->sibling = 0;
}

// FUNCTION: SADX 0x008b1400
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_HotShelter0);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	ds_DrawObjectClip(object_breakkabe_before_before, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008b1470
static void Disp2Task(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_HotShelter0);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	ds_DrawObjectClip(object_breakkabe_after_after, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008b14e0
static void ShutterPartsDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_HotShelter0);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
		}
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		ds_DrawModelClip((struct NJS_MODEL *)var1->counter.ptr, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008b1560
static void ShutterParts(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;
	switch (var1->mode)
	{
	case 0:
		FEGG_SetDynamicsWork(tp, 0);
		tp->disp = ShutterPartsDisplayer;
		var1->mode = 1;
		break;
	case 1:
		if (var1->flag & 1)
		{
			var1->btimer++;
			if (var1->btimer == 4)
			{
				var2->ang_spd.z = 0;
				var1->mode = 3;
			}
			else
			{
				FEGG_TaskActBounce(var1, var2);
				var2->ang_spd.z *= (double)0.6f;
				if (var1->btimer == 1)
				{
					shutter_smoke.pos = var1->pos;
					shutter_smoke.velo.x = (float)(rand() * 0.000030517578125) - 0.5;
					shutter_smoke.velo.y = 0.2f;
					shutter_smoke.velo.z = (float)(rand() * 0.000030517578125) - 0.5;
					shutter_smoke.scl = 3.0f;
					SHELTER_CreateSmoke(&shutter_smoke);
				}
			}
		}
		FEGG_TaskActGravity(var1, var2);
		FEGG_TaskMove(var1, var2);
		var1->ang.z += var2->ang_spd.z;
		break;
	}
	FEGG_TaskCheckGround(var1, var2);
	ShutterPartsDisplayer(tp);
}

// FUNCTION: SADX 0x008b16b0
static void CreateShutterParticles(struct taskwk *twp)
{
	njPushMatrix(0);
	njUnitMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.y)
	{
		njRotateY(0, (unsigned short)twp->ang.y);
	}
	for (int var1 = 0; var1 < 0x10000; var1 += 0x1000)
	{
		float local_c = njSin(var1);
		float local_10 = njCos(var1);
		float local_14 = (float)(rand() * 0.000030517578125) * (double)0.8f + 0.5;
		float local_8 = (float)(rand() * 0.000030517578125) * 4.0 + (double)0.8f;
		shutter_smoke.velo.z = local_14 * local_10;
		shutter_smoke.velo.y = local_14 * local_c;
		shutter_smoke.velo.x = local_8;
		local_14 = (float)(rand() * 0.000030517578125) * 20.0 + 10.0;
		shutter_smoke.pos.z = local_14 * local_10;
		shutter_smoke.pos.y = local_14 * local_c;
		shutter_smoke.pos.x = 0.0f;
		shutter_smoke.scl = (float)(rand() * 0.000030517578125) * 3.0 + 6.0;
		njCalcPoint(0, &shutter_smoke.pos, &shutter_smoke.pos);
		njCalcVector(0, &shutter_smoke.velo, &shutter_smoke.velo);
		SHELTER_CreateSmoke(&shutter_smoke);
	}
	njPopMatrix(1);
}

void FUN_008b1850(struct taskwk *param_1);

// FUNCTION: SADX 0x008b1910
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->disp = DispATask;
	tp->dest = DesertATask;
	struct obj *var2 = GetMobileLandObject();
	var1->value.ptr = var2;
	var2->evalflags = object_breakkabe_beforecoli_beforecoli[0].evalflags;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_breakkabe_beforecoli_beforecoli[0].pos[0];
	var2->pos[1] = var1->pos.y + object_breakkabe_beforecoli_beforecoli[0].pos[1];
	var2->pos[2] = var1->pos.z + object_breakkabe_beforecoli_beforecoli[0].pos[2];
	var2->model = object_breakkabe_beforecoli_beforecoli[0].model;
	var2->child = 0;
	var2->sibling = 0;
	RegisterCollisionEntry(0x20000000, tp, var2);
	var1->counter.w[0] = 0;
	var1->mode = 1;
}

// FUNCTION: SADX 0x008b19a0
static void CreateShutterParts(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	bool var10 = false;
	njPushMatrix(0);
	njUnitMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	for (struct obj *var2 = object_breakkabe_br_part_br_part[0].child; var2; var2 = var2->sibling)
	{
		struct task *var3 = CreateChildTask(3, ShutterParts, tp);
		struct taskwk *var4 = var3->twp;
		struct motionwk *var5 = var3->mwp;
		var4->smode = var10;
		var10 = !var10;
		njCalcPoint(0, (struct NJS_POINT3 *)var2->pos, &var4->pos);
		float var6 = var2->pos[0];
		float var7 = var2->pos[1];
		float var8 = var2->pos[2];
		float var9 = 1.0f / njSqrt(var8 * var8 + var6 * var6 + var7 * var7);
		var8 *= var9;
		var5->spd.z = var8 - ((float)(rand() * 0.000030517578125) * 2.5 + 1.0);
		var5->spd.y = var9 * var7;
		var5->spd.x = var9 * var6;
		njCalcVector(0, &var5->spd, &var5->spd);
		var4->counter.ptr = var2->model;
		var4->ang.y = var1->ang.y;
		var4->ang.z = 0;
		var5->ang_spd.z = 1024 - (long)((float)(rand() * 0.000030517578125) * -1024.0);
		var5->height = var1->pos.y + 3.0;
		var5->weight = 1.0f;
		for (int local_c = 3; local_c; local_c--)
		{
			var3 = CreateChildTask(3, ShutterBrokenPiece, tp);
			var4 = var3->twp;
			var5 = var3->mwp;
			FEGG_SetBrokenPiece(var4, var2->model);
			var6 = var2->pos[0];
			var7 = var2->pos[1];
			var8 = var2->pos[2];
			var6 += ((float)(rand() * 0.000030517578125) - 0.5) * 10.0;
			var7 += ((float)(rand() * 0.000030517578125) - 0.5) * 10.0;
			var8 += ((float)(rand() * 0.000030517578125) - 0.5) * 10.0;
			var4->pos.z = var8;
			var4->pos.y = var7;
			var4->pos.x = var6;
			var9 = 1.0f / njSqrt(var6 * var6 + var7 * var7 + var8 * var8);
			var8 *= var9;
			var5->spd.z = var8 - ((float)(rand() * 0.000030517578125) * 2.0 + 2.0);
			var5->spd.y = var9 * var7;
			var5->spd.x = var9 * var6;
			var4->ang.x = (long)((float)(rand() * 0.000030517578125) * 65536.0);
			var4->ang.y = var1->ang.y;
			var4->ang.z = (long)((float)(rand() * 0.000030517578125) * 65536.0);
			var4->scl.x = (float)(rand() * 0.000030517578125) + 0.5;
			var5->ang_spd.z = -2048 - (long)((float)(rand() * 0.000030517578125) * -4096.0);
			var5->height = var1->pos.y + 5.0;
			var5->weight = 1.0f;
			njCalcPoint(0, &var4->pos, &var4->pos);
			njCalcVector(0, &var5->spd, &var5->spd);
		}
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008b1dc0
void ObjShelterBreakKabe(struct task *tp)
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
			ExecATask(tp);
			if (GetSwitchOnOff(19))
			{
				var1->mode = 2;
				dsPlay_oneshot(0x149, 0, 0, 0);
			}
			break;
		case 2:
			Disp2Task(tp);
			tp->disp = Disp2Task;
			CreateShutterParts(tp);
			CreateShutterParticles(var1);
			InitBTask(tp);
			FUN_008b1850(var1);
			var1->mode = 3;
			break;
		case 3:
			Disp2Task(tp);
			FUN_008b13b0(tp);
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
			DebPrintf(0x110010, "-> ROTATE X");
			DebPrintf(0x110011, "-> ROTATE Y");
			DebPrintf(0x110012, "-> ROTATE Z");
			DispATask(tp);
			ExecATask(tp);
			break;
		}
	}
	LoopTaskC(tp);
}
