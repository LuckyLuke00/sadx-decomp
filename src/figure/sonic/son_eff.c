#include "decls.h"
extern "C" double asin(double param_1);
extern "C" double atan2(double v, double u);
void FUN_005b5aa0();
extern void *DAT_060eea60;
int FUN_005b05b0(struct taskwk *param_1);
void FUN_005b0e20(struct task *param_1);
void njScaleV(float *, struct NJS_POINT3 *);
void FUN_005ae5e0(struct taskwk *param_1, void *param_2);

// STUB: SADX 0x005ae4f0
void ObjectMizuiki(struct task *tp)
{
}

// FUNCTION: SADX 0x005ae5b0
void AwaEnd(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	while (local_8->value.ptr != 0)
	{
		FUN_005ae5e0(local_8, local_8->value.ptr);
	}
}

// FUNCTION: SADX 0x005ae5e0
void FUN_005ae5e0(struct taskwk *param_1, void *param_2)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;
	local_cg = *(struct taskwk **)((char *)param_2 + 0x2c);
	local_8g = *(struct taskwk **)((char *)param_2 + 0x30);
	if (local_cg != NULL)
	{
		*(struct taskwk **)((char *)local_cg + 0x30) = local_8g;
	}
	else
	{
		*(struct taskwk **)((char *)param_1 + 0x10) = local_8g;
	}
	if (local_8g != NULL)
	{
		*(struct taskwk **)((char *)local_8g + 0x2c) = local_cg;
	}
	Free(param_2);
}

// STUB: SADX 0x005af370
void CalcPosVec(int pnum, struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, struct NJS_POINT3 *posr)
{
}

// FUNCTION: SADX 0x005af750
void *FUN_005af750(void *param_1)
{
	void *local_8;

	local_8 = MAlloc(0x34);
	if (local_8 != 0)
	{
		*(int *)((char *)local_8 + 0x2c) = 0;
		*(void **)((char *)local_8 + 0x30) = *(void **)((char *)param_1 + 0x10);
		if (*(void **)((char *)param_1 + 0x10) != 0)
		{
			*(void **)((char *)*(void **)((char *)param_1 + 0x10) + 0x2c) = local_8;
		}
		*(void **)((char *)param_1 + 0x10) = local_8;
	}
	return local_8;
}

// STUB: SADX 0x005af7b0
void AwaDraw(struct task *tp)
{
}

// FUNCTION: SADX 0x005af870
void EffectSpin(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	EffectSpinInit(local_8);
	tp->exec = EffectSpinExecute;
	tp->disp = EffectSpinDisplay;
	EffectSpinDisplay(tp);
}

// FUNCTION: SADX 0x005af8b0
void EffectSpinDS(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	EffectSpinDSInit(local_8);
	tp->exec = EffectSpinDSExecute;
	tp->disp = EffectSpinDSDisplay;
	EffectSpinDSDisplay(tp);
}

// FUNCTION: SADX 0x005af8f0
void EffectStartHoming(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	EffectStartHomingInit(local_8);
	tp->exec = EffectStartHomingExecute;
	tp->disp = EffectStartHomingDisplay;
	EffectStartHomingDisplay(tp);
}

// STUB: SADX 0x005afdf0
void EffectStartHomingInit(struct taskwk *twp)
{
}

// STUB: SADX 0x005aff20
void EffectSpinDisplay(struct task *tp)
{
}

// STUB: SADX 0x005b0120
void EffectSpinExecute(struct task *tp)
{
}

// STUB: SADX 0x005b0180
void EffectSpinDSDisplay(struct task *tp)
{
}

// STUB: SADX 0x005b0300
void EffectSpinDSExecute(struct task *tp)
{
}

// STUB: SADX 0x005b03b0
void EffectStartHomingDisplay(struct task *tp)
{
}

// STUB: SADX 0x005b04f0
void EffectStartHomingExecute(struct task *tp)
{
}

// FUNCTION: SADX 0x005b0560
void EffectDash(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (FUN_005b05b0(local_8) == 1)
	{
		tp->exec = EffectDashExecute;
		tp->disp = EffectDashDisplay;
		tp->dest = FUN_005b0e20;
	}
	else
	{
		FreeTask(tp);
	}
}

// STUB: SADX 0x005b05b0
int FUN_005b05b0(struct taskwk *local_8)
{
	return (int)0;
}

// STUB: SADX 0x005b0740
void EffectDashDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x005b0d80
void FUN_005b0d80(struct NJS_POINT3 *param_1, int *param_2)
{
	float local_8;

	local_8 = njScalor(param_1);
	if (local_8 == 0.0f)
	{
		return;
	}
	param_2[1] = atan2(-param_1->z, param_1->x) * 65536.0 / 6.283184;
	param_2[2] = asin(param_1->y / local_8) * 65536.0 / 6.283184;
	*param_2 = 0;
}

// STUB: SADX 0x005b0e20
void FUN_005b0e20(struct task *param_1)
{
}

// STUB: SADX 0x005b1340
void EffectDrawRibbon(struct task *tp)
{
}

// STUB: SADX 0x005b1820
void EffectDestructRibbon(struct task *tp)
{
}

// STUB: SADX 0x005b18a0
void EffectExecuteRibbon(struct task *tp)
{
}

// STUB: SADX 0x005b1930
void EffectFadeRibbon(struct task *tp)
{
}

// STUB: SADX 0x005b1c50
void EffectSpinRibbonDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x005b1fc0
void SetSonicIce(long pno)
{
	struct task *local_8;

	local_8 = CreateElementalTask(2, 3, SonicIce);
	if (local_8 != NULL)
	{
		local_8->twp->btimer = pno;
	}
}

// FUNCTION: SADX 0x005b1ff0
void SonicIce(struct task *tp)
{
	struct taskwk *local_cg;
	struct playerwk *local_8g;

	local_cg = tp->twp;
	local_8g = GetPlayerWorkPointer(local_cg->btimer);
	local_cg->wtimer = *(short *)((char *)local_8g + 0x124);
	local_cg->scl.z = 1.0f;
	local_cg->scl.y = 1.0f;
	local_cg->scl.x = 1.0f;
	tp->disp = SonicIceDisplay;
	tp->exec = SonicIceExecute;
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	local_cg->counter.l = *(int *)((char *)DAT_060eea60 + 0x120);
	local_cg->value.ptr = &texlist_sonic_s_ice;
}

// FUNCTION: SADX 0x005b2080
void SonicIceDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (*(int *)((char *)local_8 + 0x1c) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)local_8 + 0x1c));
	}
	if (*(int *)((char *)local_8 + 0x14) != 0)
	{
		njRotateX(0, *(unsigned short *)((char *)local_8 + 0x14));
	}
	if (*(int *)((char *)local_8 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)local_8 + 0x18));
	}
	njScaleV(0, (struct NJS_POINT3 *)((char *)local_8 + 0x2c));
	___dsDrawObject((struct obj *)(*(int *)((char *)local_8 + 8)));
	njPopMatrix(1);
}

// STUB: SADX 0x005b2140
void SonicIceExecute(struct task *tp)
{
}

// STUB: SADX 0x005b21e0
void SetIcePieces(struct taskwk *twp)
{
}

// STUB: SADX 0x005b22a0
void SonicIcePiece(struct task *tp)
{
}

// FUNCTION: SADX 0x005b2380
void SonicIcePieceExecute(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	*(float *)((char *)local_8 + 0x20) = *(float *)((char *)local_8 + 0x20) + njSin(*(int *)((char *)local_8 + 0x18)) * 2.0f;
	*(float *)((char *)local_8 + 0x28) = *(float *)((char *)local_8 + 0x28) + njCos(*(int *)((char *)local_8 + 0x18)) * 2.0f;
	*(float *)((char *)local_8 + 0x24) = *(float *)((char *)local_8 + 0x24) + *(float *)((char *)local_8 + 0x30);
	*(float *)((char *)local_8 + 0x30) = *(float *)((char *)local_8 + 0x30) - 0.1f;
	if (*(float *)((char *)local_8 + 0x30) < -6.0f)
	{
		*(float *)((char *)local_8 + 0x30) = -6.0f;
	}
	*(int *)((char *)local_8 + 0x14) = *(int *)((char *)local_8 + 0x14) + 0x100;
	SonicIceDisplay(tp);
}
