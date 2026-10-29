#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
float FUN_00500c70(float param_1, float param_2, float param_3);

// FUNCTION: SADX 0x007d95c0
void capturebeam_draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_capturebeam);
	njPushMatrix(NULL);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	if (*(int *)((char *)var1 + 8) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 8));
	}
	FUN_0067d2d0((float *)0, var1->scl.x, var1->scl.y + 0.0, var1->scl.z);
	late_DrawObjectClip((struct obj *)&object_e000c_capturebeam_capturebeam, 0, FUN_00500c70(var1->scl.x, var1->scl.y + 0.0, var1->scl.z));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007d9870
void capturebeam_init(struct task *tp)
{
	tp->twp->scl.x = 0.0f;
	tp->twp->scl.y = 1.0f;
	tp->twp->scl.z = 0.0f;
	tp->twp->btimer = 0;
	tp->twp->counter.l = 0;
	tp->mwp->spd.x = 0.0f;
	tp->mwp->spd.z = 0.0f;
	tp->mwp->acc.x = 0.01f;
	tp->mwp->acc.y = 0.01f;
	tp->mwp->acc.z = 768.0f;
	tp->mwp->rad = 1.0f;
	tp->mwp->height = 1.0f;
	tp->twp->mode = 0;
	tp->exec = capturebeam_exec;
	tp->disp = capturebeam_draw;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007d98f0
struct task *CreateCaptureBeam(float x, float y, float z, long ax, long ay, long az)
{
	struct task *var1;
	var1 = CreateElementalTask(3, 6, capturebeam_init);
	if (var1 != 0)
	{
		var1->twp->pos.x = x;
		var1->twp->pos.y = y;
		var1->twp->pos.z = z;
		var1->twp->ang.x = ax;
		var1->twp->ang.y = ay;
		var1->twp->ang.z = az;
		return var1;
	}
	return 0;
}

// FUNCTION: SADX 0x007d9990
void SetCaptureParam(struct task *tp, float sclx, float scly, float sclz, float scl_large_spd, float scl_small_spd, long rot_spd)
{
	if (sclx > 0.0f)
	{
		tp->mwp->rad = sclx;
	}
	if (scly > 0.0f)
	{
		tp->twp->scl.y = scly;
	}
	if (sclz > 0.0f)
	{
		tp->mwp->height = sclz;
	}
	if (scl_large_spd > 0.0f)
	{
		tp->mwp->acc.x = scl_large_spd;
	}
	if (scl_small_spd > 0.0f)
	{
		tp->mwp->acc.y = scl_small_spd;
	}
	if (rot_spd > 0)
	{
		tp->mwp->acc.z = (float)rot_spd;
	}
}
