#include "decls.h"
#include <stdlib.h>

// GLOBAL: SADX 0x04ad80d0
static struct particle_info shutter_smoke;

// FOLD: the game's link folded this copy into the one of o_shelter_boxana.c (0x008aee30).
static void DesertATask(struct task *tp)
{
	struct taskwk *twp = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)twp->value.ptr);
	ReleaseMobileLandObject((struct obj *)twp->value.ptr);
}
void FUN_008af650(struct task *param_1);
extern struct task *DAT_060dd688;

// FUNCTION: SADX 0x008af040
static void FUN_008af040(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct obj *var2 = (struct obj *)var1->value.ptr;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_tv_clashSSS_corimae_corimae[0].pos[0];
	var2->pos[1] = var1->pos.y + object_tv_clashSSS_corimae_corimae[0].pos[1];
	var2->pos[2] = var1->pos.z + object_tv_clashSSS_corimae_corimae[0].pos[2];
	var2->model = object_tv_clashSSS_corimae_corimae[0].model;
	var2->child = 0;
	var2->sibling = 0;
}

// FUNCTION: SADX 0x008af090
static void FUN_008af090(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct obj *var2 = (struct obj *)var1->value.ptr;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_tv_clash_base_coris_base_coris[0].pos[0];
	var2->pos[1] = var1->pos.y + object_tv_clash_base_coris_base_coris[0].pos[1];
	var2->pos[2] = var1->pos.z + object_tv_clash_base_coris_base_coris[0].pos[2];
	var2->model = object_tv_clash_base_coris_base_coris[0].model;
	var2->child = 0;
	var2->sibling = 0;
}

// FUNCTION: SADX 0x008af0e0
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
	late_DrawObjectClip((struct obj *)&object_tv_clash_base_tv_clash_base, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008af150
void DispBTask(struct task *tp)
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawModelClip((struct NJS_MODEL *)&model_tv_clash_base_tv_clash_base, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008af1c0
static void InitBTask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
	ReleaseMobileLandObject((struct obj *)var1->value.ptr);
	struct obj *var2 = GetMobileLandObject();
	var1->value.ptr = var2;
	var2->evalflags = object_tv_clash_base_coris_base_coris[0].evalflags;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_tv_clash_base_coris_base_coris[0].pos[0];
	var2->pos[1] = var1->pos.y + object_tv_clash_base_coris_base_coris[0].pos[1];
	var2->pos[2] = var1->pos.z + object_tv_clash_base_coris_base_coris[0].pos[2];
	var2->model = object_tv_clash_base_coris_base_coris[0].model;
	var2->child = 0;
	var2->sibling = 0;
	RegisterCollisionEntry(0x20000000, tp, var2);
}

// FUNCTION: SADX 0x008af250
static void ShutterPartsDisplayer(struct task *tp)
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
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	late_DrawModelClip((struct NJS_MODEL *)var1->counter.ptr, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008af2d0
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
				var2->ang_spd.z *= UNKNOWN_DOUBLE_MACRO(0.6f);
				if (var1->btimer == 1)
				{
					shutter_smoke.pos = var1->pos;
					shutter_smoke.velo.x = (float)(rand() * 0.000030517578125) - 0.5;
					shutter_smoke.velo.y = 0.2f;
					shutter_smoke.velo.z = (float)(rand() * 0.000030517578125) - 0.5;
					shutter_smoke.scl = 3.0f;
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

// FUNCTION: SADX 0x008af410
static void BrokenPieceDisplayer(struct task *tp)
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
	if (var1->ang.x)
	{
		njRotateX(0, (unsigned short)var1->ang.x);
	}
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	FUN_0067d2d0(0, var1->scl.x, var1->scl.x, var1->scl.x);
	FEGG_DrawBrokenPiece(var1);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008af4c0
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
		float local_14 = (float)(rand() * 0.000030517578125) * 0.8f + 0.5;
		float local_8 = (float)(rand() * 0.000030517578125) * 4.0 + 0.8f;
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
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008af6f0
static void InitATask(struct task *tp)
{
	tp->disp = DispATask;
	tp->dest = DesertATask;
	struct taskwk *var1 = tp->twp;
	var1->pos.x = TVpos[0];
	var1->pos.y = TVpos[1];
	var1->pos.z = TVpos[2];
	var1->ang.x = 0;
	var1->ang.y = 0x4000;
	var1->ang.z = 0;
	DAT_060dd688 = CreateChildTask(3, ObjShelterRoboMonitor, tp);
	struct taskwk *var3 = DAT_060dd688->twp;
	var3->pos.x = 540.0f;
	var3->ang.x = 0;
	var3->pos.y = 228.0f;
	var3->ang.y = 0x4000;
	var3->pos.z = -2605.0f;
	var3->ang.z = 0;
	struct obj *var2 = GetMobileLandObject();
	var1->value.ptr = var2;
	var2->evalflags = object_tv_clashSSS_corimae_corimae[0].evalflags;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->ang[0] = 0;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = 0;
	var2->pos[0] = var1->pos.x + object_tv_clashSSS_corimae_corimae[0].pos[0];
	var2->pos[1] = var1->pos.y + object_tv_clashSSS_corimae_corimae[0].pos[1];
	var2->pos[2] = var1->pos.z + object_tv_clashSSS_corimae_corimae[0].pos[2];
	var2->model = object_tv_clashSSS_corimae_corimae[0].model;
	var2->child = 0;
	var2->sibling = 0;
	RegisterCollisionEntry(0x20000000, tp, var2);
	var1->counter.w[0] = 0;
	var1->mode = 1;
}

// FUNCTION: SADX 0x008af7e0
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

// FUNCTION: SADX 0x008af8a0
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
	for (struct obj *var2 = object_tv_clash_base_tv_clash_base[0].child; var2; var2 = var2->sibling)
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
		var6 *= var9;
		var6 -= (float)(rand() * 0.000030517578125) * 2.5 + 1.0;
		var5->spd.z = var9 * var8;
		var5->spd.y = var9 * var7;
		var5->spd.x = var6;
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
			var6 *= var9;
			var6 -= (float)(rand() * 0.000030517578125) * 2.0 + 2.0;
			var5->spd.z = var9 * var8;
			var5->spd.y = var9 * var7;
			var5->spd.x = var6;
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

// FUNCTION: SADX 0x008afcc0
void ObjShelterCrashMonitor(struct task *tp)
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
			tp->disp = 0;
			break;
		case 1:
			if (GetSwitchOnOff(5))
			{
				var1->mode = 2;
				dsPlay_oneshot(0x135, 0, 0, 0);
			}
			break;
		case 2:
			DispATask(tp);
			tp->disp = DispBTask;
			CreateShutterParts(tp);
			CreateShutterParticles(var1);
			DestroyTask(DAT_060dd688);
			InitBTask(tp);
			FUN_008af650(tp);
			var1->mode = 3;
			break;
		case 3:
			DispBTask(tp);
			FUN_008af090(tp);
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
			FUN_008af040(tp);
			break;
		}
	}
	LoopTaskC(tp);
}
