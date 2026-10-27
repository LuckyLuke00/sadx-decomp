#include "decls.h"
int FUN_007d0bd0(void);
void initMoveObjTask(struct task *p_task);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void *MAlloc(unsigned int size);
extern int DAT_060cbfb4[10];

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
	*(void **)((char *)var4 + 0x10) = var3;
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
