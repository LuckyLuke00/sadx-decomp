#include "decls.h"
void FUN_008da730(struct task *param_1);

// STUB: SADX 0x008da420
void SnakeInit(struct task *tp, struct taskwk *twp)
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

// FUNCTION: SADX 0x008daa60
void SnakePartsDisplayer(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	SnakePartsDraw(local_8);
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
	((void (*)(struct task *, struct task *, struct motionwk *))FUN_005b5aa0)(param_1, param_2, local_8);
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
void FUN_008db0b0(struct task *param_1)
{
	FreeTaskC(param_1);
	DeadOut(param_1);
}

// STUB: SADX 0x008db0d0
void SnakeWalk(struct task *tp, struct enemywk *ewp)
{
}

// STUB: SADX 0x008db160
void SnakeHeadMotion(struct taskwk *head, struct enemywk *ewp)
{
}

// STUB: SADX 0x008db230
void SnakeBodyMotion(struct taskwk *pre, struct taskwk *curr)
{
}
