#include "decls.h"
void SnakePartsFire(struct taskwk *twp);
void FUN_008da730(struct task *param_1);

// STUB: SADX 0x008da2a0
void EnemySnake(struct task *tp)
{
}

// STUB: SADX 0x008da420
void SnakeInit(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x008da4e0
void CreateSnake(struct task *tp)
{
}

// STUB: SADX 0x008da650
void SnakeParts(struct task *tp)
{
}

// STUB: SADX 0x008da730
void FUN_008da730(struct task *tp)
{
}

// STUB: SADX 0x008da810
void SnakePartsInit(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x008da900
void SnakePartsDraw(struct taskwk *twp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008daa60
void SnakePartsDisplayer(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	SnakePartsDraw(local_8);
}

// STUB: SADX 0x008daa80
void SnakePartsFire(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x008dacb0
void FUN_008dacb0(int param_1)
{
	if (((char *)param_1)[0x11] == 1)
	{
		if (*(int *)((char *)param_1 + 0x14) < 0x10000)
		{
			*(int *)((char *)param_1 + 0x14) += 0x98;
		}
		else
		{
			*(int *)((char *)param_1 + 0x14) = 0;
			((char *)param_1)[0x11] = 0;
		}
	}
}

// STUB: SADX 0x008dad00
void FUN_008dad00(struct task *tp)
{
}

// STUB: SADX 0x008dad60
void SnakePartsDead(struct task *tp)
{
}

// FUNCTION: SADX 0x008dae20
void FUN_008dae20(struct task *param_1, struct task *param_2)
{
	struct motionwk *local_8;
	local_8 = param_1->mwp;
	DestroyTask(param_1);
	FUN_005b5aa0(param_1, param_2, local_8);
}

// STUB: SADX 0x008dae60
void SnakeFire(struct task *tp)
{
}

// FUNCTION: SADX 0x008db090
void FUN_008db090(char *param_1)
{
	if (*(char *)(param_1 + 1) == 11)
	{
		*param_1 = 3;
	}
}

// FUNCTION: SADX 0x008db0b0
void FUN_008db0b0(struct task *param_1, int param_2)
{
	FreeTaskC(param_1);
	DeadOut(param_1);
}

// STUB: SADX 0x008db0d0
void SnakeWalk(struct task *tp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x008db160
void SnakeHeadMotion(struct taskwk *head, struct enemywk *ewp)
{
	*(long *)((char *)head + 0x18) = *(long *)((char *)head + 0x18) - (int)(252.0 / (*(float *)((char *)head + 0x34) * 6.283184) * 65536.0 / 360.0);
	*(float *)((char *)head + 0x20) = njCos(*(int *)((char *)head + 0x18)) * *(float *)((char *)head + 0x34) + ewp->home.x;
	*(float *)((char *)head + 0x24) = njSin((int)(ewp->nframe * 65536.0 / 360.0)) * 17.0 + ewp->home.y;
	*(float *)((char *)head + 0x28) = njSin(*(int *)((char *)head + 0x18)) * *(float *)((char *)head + 0x34) + ewp->home.z;
	ewp->nframe = ewp->nframe + 2.0;
}

// STUB: SADX 0x008db230
void SnakeBodyMotion(struct taskwk *pre, struct taskwk *curr)
{
}
