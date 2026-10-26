#include "decls.h"
extern struct _OBJ_CAMERAPARAM *DAT_05edd128;
extern struct task *DAT_060cc950;

// FUNCTION: SADX 0x007d7f00
void StgChaos6CtrlOff()
{
	struct task *var1;
	struct taskwk *var2;
	void *var3;

	if (DAT_060cc950 == 0)
		return;
	var1 = DAT_060cc950;
	var2 = var1->twp;
	var3 = *(void **)((char *)var2 + 0x10);
	*(float *)((char *)DAT_05edd128 + 0x20) = *(float *)var3;
	*(float *)((char *)DAT_05edd128 + 0x24) = *(float *)((char *)var3 + 4);
	*(float *)((char *)DAT_05edd128 + 0x28) = *(float *)((char *)var3 + 8);
	*(int *)((char *)DAT_05edd128 + 0x14) = *(int *)((char *)var3 + 0xc);
	*(int *)((char *)DAT_05edd128 + 0x18) = *(int *)((char *)var3 + 0x10);
	*(int *)((char *)DAT_05edd128 + 0x1c) = *(int *)((char *)var3 + 0x14);
	DestroyTask(var1);
	DAT_060cc950 = 0;
	EvChaosExit();
}

// FUNCTION: SADX 0x007d7f80
void StgChaos6Human2Water()
{
	EvChaos6Human2Water();
}

// FUNCTION: SADX 0x007d7f90
void StgChaos6Water2Human()
{
	EvChaos6Water2Human();
}

// FUNCTION: SADX 0x007d7fa0
void StgChaos6SetPos(float pos_x, float pos_y, float pos_z)
{
	struct taskwk *var1 = DAT_060cc950->twp;
	var1->pos.x = pos_x;
	var1->pos.y = pos_y;
	var1->pos.z = pos_z;
	*(float *)((char *)DAT_05edd128 + 0x20) = pos_x;
	*(float *)((char *)DAT_05edd128 + 0x24) = pos_y;
	*(float *)((char *)DAT_05edd128 + 0x28) = pos_z;
}

// FUNCTION: SADX 0x007d7fe0
void StgChaos6SetAng(long ang_x, long ang_y, long ang_z)
{
	struct taskwk *var1;

	var1 = DAT_060cc950->twp;
	var1->ang.x = ang_x;
	var1->ang.y = ang_y;
	var1->ang.z = ang_z;
	*(long *)((char *)DAT_05edd128 + 0x14) = ang_x;
	*(long *)((char *)DAT_05edd128 + 0x18) = ang_y;
	*(long *)((char *)DAT_05edd128 + 0x1c) = ang_z;
}

// STUB: SADX 0x007d8020
void StgChaos6CtrlOn(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z, long rot_spd)
{
}
