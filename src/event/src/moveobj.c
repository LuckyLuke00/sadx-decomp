#include "decls.h"
static void initMoveObjTask(struct task *p_task);
int FUN_007d0bd0(void);
void initMoveObjTask(struct task *p_task);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void *MAlloc(unsigned int size);
extern int DAT_060cbfb4[10];

// FUNCTION: SADX 0x007d0bd0
int FUN_007d0bd0(void)
{
	int var1 = 0;
	while (var1 < 10)
	{
		if (DAT_060cbfb4[var1] == 0)
		{
			return var1;
		}
		var1++;
	}
	return -1;
}

// FUNCTION: SADX 0x007d0bf0
void FUN_007d0bf0(struct task *param_1, struct task *param_2)
{
	int var1;
	struct task *var2;
	struct taskwk *var3;
	struct task *var4;

	for (var1 = 0; var1 < 10; var1++)
	{
		var2 = (struct task *)DAT_060cbfb4[var1];
		if (var2 != 0)
		{
			var3 = var2->twp;
			if (var3 != 0)
			{
				var4 = (struct task *)var3->value.ptr;
			}
			if (var4 != 0)
			{
				if (var4->next == param_1)
				{
					DestroyTask(var2);
					DAT_060cbfb4[var1] = 0;
				}
			}
		}
	}
}

// FUNCTION: SADX 0x007d0c40
void FUN_007d0c40(void)
{
	int var1;

	for (var1 = 0; var1 < 10; var1++)
	{
		if (DAT_060cbfb4[var1] != 0)
		{
			DestroyTask((struct task *)DAT_060cbfb4[var1]);
			DAT_060cbfb4[var1] = 0;
		}
	}
}

// FUNCTION: SADX 0x007d1460
static void initMoveObjTask(struct task *p_task)
{
	p_task->exec = execMoveObjTask;
	p_task->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
	p_task->dest = DstrMtnSpiderA;
}

// STUB: SADX 0x007d1480
void moveObject(struct task *obj, float st_x, float st_y, float st_z, float end_x, float end_y, float end_z, int frame)
{
}

// FUNCTION: SADX 0x007d1bd0
void moveObjectRightHand(struct task *obj, int player_no, float far_x, float far_y, float far_z, int frame)
{
	int var1 = FUN_007d0bd0();
	if (var1 < 0)
	{
		return;
	}
	struct task *var2 = CreateElementalTask(2, 5, initMoveObjTask);
	DAT_060cbfb4[var1] = (int)var2;
	void *var3 = MAlloc(0x6c);
	struct taskwk *var4 = ((struct task *)DAT_060cbfb4[var1])->twp;
	var4->value.ptr = var3;
	var4->pos.x = obj->twp->pos.x;
	var4->pos.y = obj->twp->pos.y;
	var4->pos.z = obj->twp->pos.z;
	*(struct task **)((char *)var3 + 0x0) = obj;
	*(float *)((char *)var3 + 0x2c) = far_x;
	*(int *)((char *)var3 + 0x5c) = player_no;
	*(float *)((char *)var3 + 0x30) = far_y;
	*(int *)((char *)var3 + 0x60) = frame;
	*(int *)((char *)var3 + 0x64) = 0;
	*(float *)((char *)var3 + 0x34) = far_z;
	*(int *)((char *)var3 + 0x68) = var1;
	if (DAT_060cbfb4[var1])
	{
		struct taskwk *var5 = ((struct task *)DAT_060cbfb4[var1])->twp;
		var5->mode = 0x13;
	}
}
