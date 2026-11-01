#include "decls.h"
extern struct obj object_cas_cl_kinko_wall_kinko_wall[1];

// FUNCTION: SADX 0x008799c0
void CasinoClearCollisionExec(struct task *tp)
{
	if (GetKinkaiNum() >= 0x190)
	{
		FreeTask(tp);
	}
}

// FUNCTION: SADX 0x008799e0
void CasinoClearCollisionDest(struct task *tp)
{
	WithdrawCollisionEntry(tp, (struct obj *)&object_cas_cl_kinko_wall_kinko_wall);
}

// FUNCTION: SADX 0x0087a440
void CasinoClearCollisionInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2;

	var2 = GetMobileLandObject();
	*(struct obj **)((char *)var1 + 8) = var2;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->evalflags = 0x10;
	var2->ang[2] = 0;
	var2->pos[2] = 0.0f;
	var2->ang[1] = 0;
	var2->pos[1] = 0.0f;
	var2->ang[0] = 0;
	var2->pos[0] = 0.0f;
	var2->model = object_cas_cl_kinko_wall_kinko_wall[0].model;
	var2->child = object_cas_cl_kinko_wall_kinko_wall[0].child;
	var2->sibling = object_cas_cl_kinko_wall_kinko_wall[0].sibling;
	RegisterCollisionEntry(0x18000001, tp, var2);
	tp->exec = CasinoClearCollisionExec;
	tp->dest = CasinoClearCollisionDest;
}

// FUNCTION: SADX 0x0087a520
void ObjectCasinoShakeHand(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		if (GetPlayerNumber() == 0)
		{
			CreateElementalTask(2, 6, CasinoClearCollisionInit);
		}
		ObjectCasinoShakeHandInit(tp);
	}
}
