#include "decls.h"
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

// STUB: SADX 0x007d2f40
void MoveChaos0(float pos_x, float pos_y, float pos_z, int frame)
{
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
