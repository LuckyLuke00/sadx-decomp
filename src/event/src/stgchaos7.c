#include "decls.h"
extern struct task *DAT_060cc4c8;
extern struct _OBJ_CAMERAPARAM *DAT_05edd128;

// FUNCTION: SADX 0x007d56a0
void StgChaos7Howl1()
{
	EvChaos7Howl1();
}

// FUNCTION: SADX 0x007d56b0
void StgChaos7Breath(float length)
{
	EvChaos7Breath(length);
}

// FUNCTION: SADX 0x007d56c0
void StgChaos7SetPos(float pos_x, float pos_y, float pos_z)
{
	struct taskwk *var1 = DAT_060cc4c8->twp;
	var1->pos.x = pos_x;
	var1->pos.y = pos_y;
	var1->pos.z = pos_z;
	*(float *)((char *)DAT_05edd128 + 0x20) = pos_x;
	*(float *)((char *)DAT_05edd128 + 0x24) = pos_y;
	*(float *)((char *)DAT_05edd128 + 0x28) = pos_z;
}

// FUNCTION: SADX 0x007d5700
void StgChaos7SetAng(long ang_x, long ang_y, long ang_z)
{
	struct taskwk *var1;

	var1 = DAT_060cc4c8->twp;
	var1->ang.x = ang_x;
	var1->ang.y = ang_y;
	var1->ang.z = ang_z;
	*(long *)((char *)DAT_05edd128 + 0x14) = ang_x;
	*(long *)((char *)DAT_05edd128 + 0x18) = ang_y;
	*(long *)((char *)DAT_05edd128 + 0x1c) = ang_z;
}

// STUB: SADX 0x007d5740
void StgChaos7CtrlOn(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z, long rot_spd)
{
}
