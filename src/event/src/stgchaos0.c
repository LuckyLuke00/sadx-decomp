#include "decls.h"
extern struct _OBJ_CAMERAPARAM *DAT_05edd128;
extern struct task *DAT_060cceb4;
void FUN_007d6940(struct task *param_1);

// FUNCTION: SADX 0x007dc950
void initChaos0CtrlTask(struct task *task_p)
{
	task_p->exec = execChaos0CtrlTask;
	task_p->disp = 0;
	task_p->dest = FUN_007d6940;
}

// STUB: SADX 0x007e0520
void StgChaos0CtrlOff()
{
}

// FUNCTION: SADX 0x007e05a0
void StgChaos0SetPos(float pos_x, float pos_y, float pos_z)
{
	struct taskwk *var1 = DAT_060cceb4->twp;
	var1->pos.x = pos_x;
	var1->pos.y = pos_y;
	var1->pos.z = pos_z;
	*(float *)((char *)DAT_05edd128 + 0x20) = pos_x;
	*(float *)((char *)DAT_05edd128 + 0x24) = pos_y;
	*(float *)((char *)DAT_05edd128 + 0x28) = pos_z;
}

// FUNCTION: SADX 0x007e05e0
void StgChaos0SetAng(long ang_x, long ang_y, long ang_z)
{
	struct taskwk *var1;

	var1 = DAT_060cceb4->twp;
	var1->ang.x = ang_x;
	var1->ang.y = ang_y;
	var1->ang.z = ang_z;
	*(long *)((char *)DAT_05edd128 + 0x14) = ang_x;
	*(long *)((char *)DAT_05edd128 + 0x18) = ang_y;
	*(long *)((char *)DAT_05edd128 + 0x1c) = ang_z;
}

// STUB: SADX 0x007e0620
void StgChaos0CtrlOn(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z, long rot_spd)
{
}
