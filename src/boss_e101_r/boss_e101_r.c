#include "decls.h"
void flickE102Shot(struct task *pTask);
extern void (*DAT_05b9e0b0)();
extern void *DAT_060c4570;
extern int DAT_060c462c;
extern unsigned int *DAT_05b93264;
extern void *DAT_060c4574;

// FUNCTION: SADX 0x00707650
void _boss_e101_r_epilog()
{
	changere101rend();
	syFree(DAT_060c4574);
}

// FUNCTION: SADX 0x00707670
void destE101R(struct task *pTask)
{
	struct anywk *var1 = pTask->awp;
	struct taskwk *var2 = pTask->twp;

	E101R_EfShotFlickExit();
	E101R_BarrierExit();
	FUN_007d21b0();
	E101R_EfWaveAccumeExit();
	E101R_NozzleLightExit();
	*(short *)((char *)var1 + 4) = 0xe;
	BSetMotion(var2, (struct bosswk *)var1);
	TikalBossKill();
}

// STUB: SADX 0x007078a0
void selectMode(struct task *pTask)
{
}

// STUB: SADX 0x00707b30
void flickE102Shot(struct task *pTask)
{
}

// STUB: SADX 0x007082d0
void moveParts(struct task *pTask)
{
}

// STUB: SADX 0x00708420
void calcAttackStartPos(struct task *pTask)
{
}

// STUB: SADX 0x00708820
void FUN_00708820(struct task *param_1, struct taskwk *param_2)
{
}

// FUNCTION: SADX 0x0070a380
void edit(struct task *pTask)
{
	if ((*(int *)((char *)DAT_05b93264 + 0x10) & 6) != 0)
	{
		if (pTask->twp->mode != 1)
		{
			*(int *)((char *)pTask->awp + 0x4c) = 1;
			*(int *)((char *)pTask->awp + 0x50) = pTask->twp->mode;
		}
		CameraSetEventCamera(0x37, 0);
	}
}

// FUNCTION: SADX 0x0070a3c0
void callbackE101R(struct obj *obj)
{
	if (obj == (struct obj *)(DAT_060c462c + 0x8238))
	{
		FUN_0067d830((float *)0x0, 0.0f, 0.0f, *(float *)((char *)DAT_060c4570 + 0x174));
	}
}

// FUNCTION: SADX 0x0070a690
void _boss_e101_r_prolog()
{
	DAT_060c4574 = syMalloc(0x4b800);
	changere101rinit();
	DAT_05b9e0b0 = _boss_e101_r_epilog;
}

// STUB: SADX 0x0070a850
void SetE101_R()
{
}
