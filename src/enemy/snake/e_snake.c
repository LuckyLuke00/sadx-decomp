#include "decls.h"
extern struct CCL_INFO head_colli_info[1];
extern struct CCL_INFO parts0_colli_info[4];
extern struct CCL_INFO parts1_colli_info[3];
extern struct CCL_INFO tail_colli_info[1];
extern char snake_parts[132];
void SnakePartsDead(struct task *tp);
void SnakeHeadMotion(struct taskwk *head, struct enemywk *ewp);
void SnakeBodyMotion(struct taskwk *pre, struct taskwk *curr);
extern int DAT_05b9d838;
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

// FUNCTION: SADX 0x008da4e0
void CreateSnake(struct task *tp)
{
	struct taskwk *local_18;
	struct task *local_14;
	int local_10;
	float local_ci;
	struct taskwk *local_8g;

	local_18 = tp->twp;
	local_ci = 0.0f;
	if (local_18->scl.z < 60.0)
	{
		local_18->scl.z = 60.0f;
	}
	else if (local_18->scl.z > 150.0)
	{
		local_18->scl.z = 150.0f;
	}
	for (local_10 = 0; local_10 < 11; local_10++)
	{
		local_14 = CreateChildTask(2, SnakeParts, tp);
		if (local_14 != 0)
		{
			local_8g = local_14->twp;
			local_ci += *(float *)(snake_parts + local_10 * 0xc + 8);
			local_8g->pos.x = local_18->pos.x - njCos(local_18->ang.y) * local_ci;
			local_8g->pos.y = njSin((long)(local_10 * 45.0 * 65536.0 / 360.0)) * 12.0 + local_18->pos.y;
			local_8g->pos.z = local_18->pos.z - njSin(local_18->ang.y) * local_ci;
			local_8g->ang.x = local_18->ang.x;
			local_8g->ang.y = local_18->ang.y;
			local_8g->ang.z = local_18->ang.z;
			local_8g->btimer = 0;
			local_8g->wtimer = 0;
			local_8g->scl.z = local_18->scl.z;
			local_8g->smode = local_10;
		}
	}
}

// STUB: SADX 0x008da650
void SnakeParts(struct task *tp)
{
}

// STUB: SADX 0x008da730
void FUN_008da730(struct task *param_1)
{
}

// FUNCTION: SADX 0x008da810
void SnakePartsInit(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (EnemyInitialize(tp, local_8) == 0)
	{
		Free(tp->ptp);
		return;
	}
	switch (local_8->smode)
	{
	case 0:
		break;
	case 1:
		CCL_Init(tp, head_colli_info, 1, 2);
		break;
	case 2:
	case 9:
		CCL_Init(tp, parts0_colli_info, 2, 2);
		break;
	default:
		CCL_Init(tp, parts1_colli_info, 2, 2);
		break;
	case 10:
		CCL_Init(tp, tail_colli_info, 1, 2);
		break;
	}
	local_8->value.b[0] = 0;
	local_8->value.b[2] = 0;
	local_8->mode = 1;
}

// STUB: SADX 0x008da900
void SnakePartsDraw(struct taskwk *twp)
{
}

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

// FUNCTION: SADX 0x008dad00
void FUN_008dad00(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (local_8->btimer++ < local_8->wtimer)
	{
		SnakePartsDraw(local_8);
	}
	else
	{
		SnakePartsDead(param_1);
	}
	SnakePartsDraw(local_8);
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

// FUNCTION: SADX 0x008db0d0
void SnakeWalk(struct task *tp, struct enemywk *ewp)
{
	struct taskwk *local_10;
	struct task *local_cj;
	int local_8g;

	local_10 = tp->twp;
	local_cj = tp->ctp;
	while (local_cj->next != 0)
	{
		local_cj = local_cj->next;
	}
	SnakeHeadMotion(local_cj->twp, ewp);
	for (local_8g = 0; local_8g < 10; local_8g++)
	{
		if (local_cj == 0 || local_cj->last == 0)
		{
			continue;
		}
		SnakeBodyMotion(local_cj->twp, local_cj->last->twp);
		local_cj = local_cj->last;
	}
}

// FUNCTION: SADX 0x008db160
void SnakeHeadMotion(struct taskwk *head, struct enemywk *ewp)
{
	head->ang.y = head->ang.y - (int)(252.0 / (head->scl.z * 6.283184) * 65536.0 / 360.0);
	head->pos.x = njCos(head->ang.y) * head->scl.z + ewp->home.x;
	head->pos.y = njSin((int)(ewp->nframe * 65536.0 / 360.0)) * 17.0 + ewp->home.y;
	head->pos.z = njSin(head->ang.y) * head->scl.z + ewp->home.z;
	ewp->nframe = ewp->nframe + 2.0;
}

// STUB: SADX 0x008db230
void SnakeBodyMotion(struct taskwk *pre, struct taskwk *curr)
{
}

// FUNCTION: SADX 0x008db3d0
void FUN_008db3d0(struct obj *param_1)
{
	float local_8;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	local_8 = *(float *)((char *)param_1 + 0x34);
	if (local_8 < 60.0f)
	{
		local_8 = 60.0f;
	}
	else if (local_8 > 150.0f)
	{
		local_8 = 150.0f;
	}
	___dsSetPalette(6);
	njPushMatrix(0);
	FUN_0067d830(0, param_1->scl[0], param_1->scl[1], param_1->scl[2]);
	UNKNOWN_ROTATE_Y_MACRO(0, param_1->ang[1]);
	UNKNOWN_ROTATE_Y_MACRO(0, 0xc000);
	___njSetTexture(&texlist_e_snake);
	___dsDrawObject(&object_snake_head_head[0]);
	njPopMatrix(1);
	___dsSetPalette(0);
}
