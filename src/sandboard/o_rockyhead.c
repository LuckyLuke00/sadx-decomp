#include "decls.h"
extern char DAT_035af710[4];
extern char DAT_060cd39c[4];

// GLOBAL: SADX 0x00a0c8d8
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_035af6f4;
extern struct ActionParam DAT_035af6bc;
extern int DAT_05b9d838;
extern struct ActionParam DAT_035af6d8;

// FUNCTION: SADX 0x007e8920
struct task *SetRockyHead01Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af6bc);
}

// FUNCTION: SADX 0x007e8940
struct task *SetRockyHead02Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af6d8);
}

// FUNCTION: SADX 0x007e8960
struct task *SetRockyHead03Task()
{
	return SandObjSetChildTask(&ObjectTaskInfo, &DAT_035af6f4);
}

// FUNCTION: SADX 0x007e8a00
void execObject(struct task *task_p)
{
	struct motionwk *var1 = task_p->mwp;
	switch (var1->work.b[0])
	{
	case 0:
		if (CheckCollisionP((struct NJS_POINT3 *)(var1->ang_aim.z), 2000.0f) != 0)
		{
			MirenSetChildTask(task_p, &RockyHeadTaskInfo, &DAT_060cd39c);
			var1->work.b[0] = 1;
		}
		break;
	case 2:
		if (CheckCollisionP((struct NJS_POINT3 *)(var1->ang_aim.z), 2000.0f) != 0)
		{
			MirenSetChildTask(task_p, &RockyHeadTaskInfo, &DAT_035af710);
			var1->work.b[0] = 1;
		}
		break;
	default:
		if (CheckCollisionP((struct NJS_POINT3 *)(var1->ang_aim.z), 2500.0f) == 0)
		{
			FreeTaskC(task_p);
			var1->work.b[0] = 2;
		}
		else
		{
			LoopTaskC(task_p);
			if (task_p->ctp == 0)
			{
				var1->work.b[0] = 0;
			}
		}
		break;
	}
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
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)var1->ang.x);
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
