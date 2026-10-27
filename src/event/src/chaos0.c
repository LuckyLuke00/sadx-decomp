#include "decls.h"
static void initChaos0Task(struct task *p_task);
static void execChaos0Task(struct task *p_task);
static void dispChaos0Task(struct task *p_task);
extern struct PL_JOIN_VERTEX ev_chaos0_jv_list[1];
extern struct NJS_ACTION _action_c0_wait0[1];
extern struct task *DAT_060cc140;

// STUB: SADX 0x007d2d80
void Jump2Chaos0(float pos_x, float pos_y, float pos_z, float jumph, int frame)
{
}

// STUB: SADX 0x007d2e60
void Jump3Chaos0(float pos_x, float pos_y, float pos_z, float jumph, int frame)
{
}

// FUNCTION: SADX 0x007d2f40
void MoveChaos0(float pos_x, float pos_y, float pos_z, int frame)
{
	struct taskwk *var1 = DAT_060cc140->twp;
	struct motionwk *var2 = (struct motionwk *)var1->value.ptr;
	*(float *)var2 = pos_x;
	*(float *)((char *)var2 + 4) = pos_y;
	*(float *)((char *)var2 + 8) = pos_z;
	*(float *)((char *)var2 + 0x18) = (pos_x - var1->pos.x) / (float)frame;
	*(float *)((char *)var2 + 0x1c) = (pos_y - var1->pos.y) / (float)frame;
	*(float *)((char *)var2 + 0x20) = (pos_z - var1->pos.z) / (float)frame;
	*(int *)((char *)var2 + 0x30) = frame;
	var1->mode = 6;
	var1->counter.f = 0.0f;
	var1->timer.l = 0;
}

// FUNCTION: SADX 0x007d2fb0
struct task *GetChaos0()
{
	return DAT_060cc140;
}

// FUNCTION: SADX 0x007d2fc0
void ChangeMotspd(float mot_spd)
{
	*(float *)((char *)DAT_060cc140->twp->value.ptr + 0x3c) = mot_spd;
}

// FUNCTION: SADX 0x007d3020
void SetPositionChaos0(float pos_x, float pos_y, float pos_z)
{
	struct taskwk *var1;
	var1 = DAT_060cc140->twp;
	var1->pos.x = pos_x;
	var1->pos.y = pos_y;
	var1->pos.z = pos_z;
}

// FUNCTION: SADX 0x007d3040
void SetAngleChaos0(long ang_x, long ang_y, long ang_z)
{
	struct taskwk *var1 = DAT_060cc140->twp;
	var1->ang.x = ang_x;
	var1->ang.y = ang_y;
	var1->ang.z = ang_z;
}

// FUNCTION: SADX 0x007d3090
void SetSclChaos0(float scl_x, float scl_y, float scl_z)
{
	struct taskwk *var1;
	var1 = DAT_060cc140->twp;
	var1->scl.x = scl_x;
	var1->scl.y = scl_y;
	var1->scl.z = scl_z;
}

// FUNCTION: SADX 0x007d30b0
void CngMotStand2Chaos0()
{
	DAT_060cc140->twp->mode = 7;
}

// FUNCTION: SADX 0x007d30c0
void CngMotStand4Chaos0()
{
	DAT_060cc140->twp->mode = 9;
}

// FUNCTION: SADX 0x007d30d0
void CngMotFlyChaos0()
{
	DAT_060cc140->twp->mode = 10;
}

#pragma optimize("", off)
// STUB: SADX 0x007d30e0
static void dispChaos0Task(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007d3ac0
void destChaos0Task(struct task *p_task)
{
	struct taskwk *var1;

	var1 = p_task->twp;
	ChaosJoinVertexes(ev_chaos0_jv_list, _action_c0_wait0, var1->counter.f, 0x48, 2);
	if (var1->value.ptr != NULL)
	{
		Free(var1->value.ptr);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x007d3b00
static void execChaos0Task(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007d3f70
static void initChaos0Task(struct task *p_task)
{
	p_task->exec = execChaos0Task;
	p_task->disp = dispChaos0Task;
	p_task->dest = destChaos0Task;
}

// FUNCTION: SADX 0x007d3f90
void CreateChaos0(float pos_x, float pos_y, float pos_z, long ang_x, long ang_y, long ang_z, int cng_int)
{
	struct taskwk *var1;
	char *var2;
	float var3;
	float var4;

	DAT_060cc140 = CreateElementalTask(2, 5, initChaos0Task);
	var2 = (char *)MAlloc(0x7c);
	var1 = DAT_060cc140->twp;
	var1->pos.x = pos_x;
	var1->ang.x = ang_x;
	var1->pos.y = pos_y;
	var1->ang.y = ang_y;
	var1->pos.z = pos_z;
	var1->ang.z = ang_z;
	var1->scl.x = 1.0f;
	var1->scl.y = 1.0f;
	var1->value.ptr = var2;
	var1->scl.z = 1.0f;
	var1->mode = 0;
	var1->counter.f = 0.0f;
	*(float *)(var2 + 0x3c) = 1.0f;
	*(int *)(var2 + 0x40) = cng_int;
	*(float *)(var2 + 0x44) = 0.0f;
	*(int *)(var2 + 0x78) = 0;
	var3 = (float)cng_int;
	var4 = 25.0f / var3;
	*(float *)(var2 + 0x48) = var4;
	*(float *)(var2 + 0x4c) = 2.0f;
	*(float *)(var2 + 0x54) = 2.0f;
	*(float *)(var2 + 0x50) = 1.0f;
	*(float *)(var2 + 0x58) = 0.2f / var3;
	*(float *)(var2 + 0x5c) = 1.0f / var3;
	*(float *)(var2 + 0x60) = 0.2f / var3;
	*(float *)(var2 + 0x64) = 0.8f;
	*(float *)(var2 + 0x68) = 0.01f;
	*(float *)(var2 + 0x6c) = 0.8f;
	*(float *)(var2 + 0x70) = 0.05f;
	*(float *)(var2 + 0x74) = 0.5f / var3;
	ChaosJoinVertexes(ev_chaos0_jv_list, _action_c0_wait0, var1->counter.f, 0x48, 0);
}
