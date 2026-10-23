#include "decls.h"
extern struct CCL_INFO cuberange_info[1];
extern struct CCL_INFO cube_info[1];
extern struct CCL_INFO cylinder_info[1];
extern struct CCL_INFO sphere_info[1];

// FUNCTION: SADX 0x0061cc20
void ColliSphere(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 0);
	}
	else
	{
		CheckRangeOut(tp);
		switch (local_8->mode)
		{
		case 0:
			CCL_Init(tp, &sphere_info[0], 1, 4);
			FUN_0061d220(local_8);
			local_8->mode = 1;
			break;
		case 1:
			EntryColliList(local_8);
			break;
		default:
			local_8->mode = 0;
			break;
		}
	}
}

// FUNCTION: SADX 0x0061d220
void FUN_0061d220(struct taskwk *param_1)
{
	struct CCL_INFO *local_8 = param_1->cwp->info;
	local_8->a = param_1->scl.x + 10.0;
	local_8->b = param_1->scl.y + 10.0;
	local_8->c = param_1->scl.z + 10.0;
	CalcColliRange(param_1->cwp);
}

// FUNCTION: SADX 0x0061d280
void ColliCylinder(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 1);
	}
	else
	{
		CheckRangeOut(tp);
		switch (local_8->mode)
		{
		case 0:
			CCL_Init(tp, &cylinder_info[0], 1, 4);
			FUN_0061d220(local_8);
			local_8->mode = 1;
			break;
		case 1:
			EntryColliList(local_8);
			break;
		default:
			local_8->mode = 0;
			break;
		}
	}
}

// FUNCTION: SADX 0x0061d310
void ColliCube(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 3);
		return;
	}
	CheckRangeOut(tp);
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &cube_info[0], 1, 4);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d430
void ColliCircle(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckEditMode())
	{
		ColliSpaceEditMode(tp, 0xa);
		return;
	}
	CheckRangeOutWithR(tp, 9000000.0f);
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &circle_info[0], 1, 8);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d4d0
void ColliOttottoRange(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (CheckRangeOut(tp) != 0)
		return;
	if (CheckEditMode() != 0)
	{
		ColliOttottoRangeEditMode(tp);
		return;
	}
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &cuberange_info[0], 1, 4);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		local_8->id = 0xc;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}

// FUNCTION: SADX 0x0061d8b0
void ColliBigWaterJumpRange(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (CheckEditMode() != 0)
	{
		ColliSpaceEditMode(tp, 3);
		return;
	}
	switch (local_8->mode)
	{
	case 0:
		CCL_Init(tp, &cuberange_info[0], 1, 4);
		FUN_0061d220(local_8);
		local_8->mode = 1;
		local_8->id = 0xd;
		break;
	case 1:
		EntryColliList(local_8);
		break;
	default:
		local_8->mode = 0;
		break;
	}
}
