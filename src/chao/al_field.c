#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x004516c0
void AL_FieldExecutor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->smode != 0)
	{
		if (var1->wtimer == 0)
		{
			DestroyTask(tp);
			return;
		}
		var1->wtimer--;
	}
	CCL_Entry(tp);
}

// FUNCTION: SADX 0x004516f0
void AL_FieldDisplayer(struct task *tp)
{
	struct taskwk *var1;
	float var2;

	var1 = tp->twp;
	var2 = var1->scl.x;
	if (ChaoGlobal.DispField == 0)
	{
		return;
	}
	SaveControl3D();
	OnControl3D(0x10);
	OffControl3D(0x200);
	SetMaterial(0.25f, 0.0f, 0.0f, 1.0f);
	njPushMatrixEx();
	njTranslateEx(&var1->pos);
	FUN_0067d2d0((float *)0, var2, var2, var2);
	njPopMatrixEx();
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	LoadControl3D();
}

// FUNCTION: SADX 0x00451790
void AL_ChildFieldDestructor(struct task *tp)
{
	if (tp->ptp != NULL)
	{
		*(int *)((char *)tp->ptp->twp + 0x50) = 0;
	}
}

// FUNCTION: SADX 0x004517b0
void FUN_004517b0(struct task *param_1, int param_2)
{
	int *var1 = (int *)((int *)param_1->twp);
	if (param_2 > 0)
	{
		*(char *)((char *)var1 + 1) = 1;
		*(short *)((char *)var1 + 6) = (short)param_2;
	}
	else
	{
		*(char *)((char *)var1 + 1) = 0;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x004517d0
struct task *AL_AllFieldCreateTT(unsigned long kind, struct NJS_POINT3 *pPos, float radius, long WaitTime, long ActiveTime)
{
	return (struct task *)0;
}
#pragma optimize("", on)

// STUB: SADX 0x00451850
struct task *AL_ChildFieldCreateT(struct task *pParentTask, unsigned long kind, struct NJS_POINT3 *pPos, float radius, long time)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x004518d0
struct task *AL_AllFieldCreateT(unsigned long kind, struct NJS_POINT3 *pPos, float radius, long time)
{
	return AL_AllFieldCreateTT(kind, pPos, radius, 0, time);
}
