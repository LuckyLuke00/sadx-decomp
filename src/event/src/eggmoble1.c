#include "decls.h"
void FUN_0067d830(float *, float, float, float);
extern struct task *DAT_060ccdc4;

// FUNCTION: SADX 0x007ddaa0
void DeleteEggmoble1()
{
	if (DAT_060ccdc4)
	{
		FreeTask(DAT_060ccdc4);
		DAT_060ccdc4 = 0;
	}
}

// STUB: SADX 0x007ddac0
void MoveEggmoble1(float tar_x, float tar_y, float tar_z)
{
}

// FUNCTION: SADX 0x007ddb10
void SetEggmoble1(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z)
{
	struct taskwk *var1;

	var1 = DAT_060ccdc4->twp;
	var1->pos.x = pos_x;
	var1->pos.y = pos_y;
	var1->ang.x = ang_x;
	var1->pos.z = pos_z;
	var1->ang.y = ang_y;
	var1->ang.z = ang_z;
}

// FUNCTION: SADX 0x007ddb50
void JetNoneEggmoble1()
{
	evChgEgm1Jet((Egm1JetCmdEnum)0);
}

// FUNCTION: SADX 0x007ddb60
void JetNormalEggmoble1()
{
	evChgEgm1Jet((Egm1JetCmdEnum)1);
}

// FUNCTION: SADX 0x007ddb70
void JetLargeEggmoble1()
{
	evChgEgm1Jet((Egm1JetCmdEnum)2);
}

// FUNCTION: SADX 0x007ddb80
void JetMaxEggmoble1()
{
	evChgEgm1Jet((Egm1JetCmdEnum)3);
}

// STUB: SADX 0x007ddb90
void ChangeSpeedEggmoble1(float speed)
{
}

// STUB: SADX 0x007ddcd0
int FUN_007ddcd0(float *param_1, float *param_2)
{
	return (int)0;
}

// STUB: SADX 0x007ddd60
float FUN_007ddd60(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6)
{
	return (float)0;
}

// STUB: SADX 0x007dddc0
void sprayEggmoble1Parts(struct obj *obj)
{
}

// FUNCTION: SADX 0x007dde30
void dispSplashEggmoble1Parts(struct obj *obj)
{
	do
	{
		njPushMatrix(0);
		FUN_0067d830(0, obj->pos[0], obj->pos[1], obj->pos[2]);
		ds_DrawModelClip(obj->model, 1.0f);
		njPopMatrix(1);
		if (obj->child != 0)
		{
			dispSplashEggmoble1Parts(obj->child);
		}
		obj = obj->sibling;
	}
	while (obj != 0);
}

// FUNCTION: SADX 0x007de080
void destEggmoble1Task(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;

	evFreeEgm1JetTask();
	if (var1->value.ptr != 0)
	{
		Free(var1->value.ptr);
		var1->value.ptr = 0;
	}
}

// FUNCTION: SADX 0x007de3c0
void initEggmoble1Task(struct task *p_task)
{
	p_task->exec = execEggmoble1Task;
	p_task->disp = dispEggmoble1Task;
	p_task->dest = destEggmoble1Task;
}

// STUB: SADX 0x007de3e0
void CreateEggmoble1(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z)
{
}
