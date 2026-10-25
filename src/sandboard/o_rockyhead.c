#include "decls.h"
extern int DAT_05b9d838;
extern struct ActionParam DAT_035af6d8;

// FUNCTION: SADX 0x007e8920
struct task *SetRockyHead01Task()
{
	static struct ActionParam var1;
	return SandObjSetChildTask(&ObjectTaskInfo, (void *)0x35af6bc);
}

// FUNCTION: SADX 0x007e8940
struct task *SetRockyHead02Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af6d8);
}

// FUNCTION: SADX 0x007e8960
struct task *SetRockyHead03Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, (void *)0x35af6f4);
}

// FUNCTION: SADX 0x007e8ad0
void dispRockyHead(struct task *task_p)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	struct taskwk *var1 = task_p->twp;
	struct motionwk *var2 = task_p->mwp;
	float var3 = *(float *)((char *)task_p->ptp->mwp + 0x1c);
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

// STUB: SADX 0x007e8b80
void FUN_007e8b80(float *param_1, float *param_2, float *param_3)
{
}
