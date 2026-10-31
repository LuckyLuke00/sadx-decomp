#include "decls.h"
static void TaskInit(struct task *tp);
static void TaskExec(struct task *tp);
static void TaskEnd(struct task *tp);
static void TaskDisp(struct task *tp);

// STUB: SADX 0x0088b810
void EffEnemyBombReflectPlayer(struct taskwk *twp)
{
}

// STUB: SADX 0x0088b8d0
void EffEnemyBombReflectPlayerSmall(struct taskwk *twp)
{
}

// STUB: SADX 0x0088c2d0
static void TaskEnd(struct task *tp)
{
}

// STUB: SADX 0x0088c310
static void TaskDisp(struct task *tp)
{
}

// STUB: SADX 0x0088c320
static void TaskExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0088c360
static void TaskInit(struct task *tp)
{
	tp->exec = TaskExec;
	tp->disp = TaskDisp;
	tp->dest = TaskEnd;
}

// FUNCTION: SADX 0x0088c380
struct task *CreateEffEnemyBombTask(struct NJS_POINT3 *posorg, struct Angle3 *angle, struct NJS_POINT3 *vecofs, struct NJS_POINT3 *vecacc, float wallposy, struct EFFENEMYBOMBPARAM *pefparam)
{
	struct task *local_8;
	struct taskwk *local_4;

	local_8 = CreateElementalTask(2, 3, TaskInit);
	if (local_8 != 0)
	{
		local_4 = local_8->twp;
		local_4->pos = *posorg;
		local_4->counter.l = (long)CreateEffEnemyBomb(posorg, angle, vecofs, vecacc, wallposy, pefparam);
		VibShot(0, 0);
		dsPlay_oneshot(0x1a, 0, 0, 0);
	}
	else
	{
		local_8 = 0;
	}
	return local_8;
}
