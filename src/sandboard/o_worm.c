#include "decls.h"
extern void njPushMatrix(float *);
extern void njTranslateV(float *, struct NJS_POINT3 *);
extern void njRotateY(float *, unsigned short);
extern void njRotateX(float *, unsigned short);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
long SetObjectTexture();
void ds_DrawObjectClip(struct obj *obj, float clipScl);
void njPopMatrix(int param_1);
extern int DAT_05b9d838;
extern char DAT_035af7e0[1];
extern void *DAT_035af79c;
// GLOBAL: SADX 0x00a0ee64
static struct TaskInfo ObjectTaskInfo;

// STUB: SADX 0x007e8ec0
struct task *SetWorm01Task()
{
	return (struct task *)0;
}

// STUB: SADX 0x007e8ee0
struct task *SetWorm02Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, (void *)0x35af758);
}

// FUNCTION: SADX 0x007e8f00
struct task *SetWorm03Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af79c);
}

// FUNCTION: SADX 0x007e8f20
struct task *SetSmallWorm01Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af7e0);
}

// FUNCTION: SADX 0x007e8fe0
void dispWorm(struct task *task_p)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	struct taskwk *var1 = task_p->twp;
	struct motionwk *var2 = task_p->mwp;
	float var3 = *(float *)((char *)task_p->ptp->mwp + 0x10);
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
	}
	FUN_0067d2d0((float *)0, var3, var3, var3);
	SetObjectTexture();
	ds_DrawObjectClip((struct obj *)(*(int *)((char *)var2 + 8)), var3);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007e9090
void destWorm(struct task *task_p)
{
	MirenObjFreeMobileLandObject(task_p, *(struct obj **)((char *)task_p->mwp + 0xc));
}
