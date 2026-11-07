#include "decls.h"
static void Draw(struct task *tp);
void FUN_008babc0(struct obj *param_1);
void FUN_008bac40(struct taskwk *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bae10(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008babc0(struct obj *param_1);
void FUN_008bac40(struct taskwk *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bae10(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bb1a0(void *param_1);
void BaloonScale(struct taskwk *twp);
void FUN_008babc0(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bae10(struct obj *param_1);

// FUNCTION: SADX 0x008baad0
void ObjectBaloon(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
		return;
	switch (local_8->mode)
	{
		case 0:
			tp->dest = (void (__cdecl *)(struct task *))FUN_005b5aa0;
			tp->disp = Draw;
			CCL_Init(tp, baloon_colli_info, 2, 4);
			FUN_008babc0((struct obj *)local_8);
			break;
		case 1:
			FUN_008bac40(local_8);
			break;
		case 2:
			FUN_008bad70((struct obj *)local_8);
			break;
		case 3:
			FUN_008bae10((struct obj *)local_8);
			break;
		case 4:
			FUN_005b5aa0(tp);
			DeadOut(tp);
		default:
			local_8->mode = 0;
			break;
	}
	Draw(tp);
}

// STUB: SADX 0x008babc0
void FUN_008babc0(struct obj *param_1)
{
}

// STUB: SADX 0x008bac40
void FUN_008bac40(struct taskwk *param_1)
{
}

// STUB: SADX 0x008bad70
void FUN_008bad70(struct obj *param_1)
{
}

// FUNCTION: SADX 0x008bae10
void FUN_008bae10(struct obj *param_1)
{
	struct task *local_8g;
	struct taskwk *local_cg;
	FUN_008bb1a0(param_1);
	BaloonScale((struct taskwk *)param_1);
	if (param_1->pos[2] < 344.0)
	{
		param_1->pos[2] = (njSin(*(int *)((char *)param_1 + 8) * 200) * 0.5 + 0.30000001192092896) * 0.5 + param_1->pos[2];
	}
	*(int *)((char *)param_1 + 8) = *(int *)((char *)param_1 + 8) + 1;
	local_8g = GetPlayerTaskPointer(0);
	local_cg = local_8g->twp;
	local_cg->pos = *(NJS_POINT3 *)((char *)param_1 + 0x20);
	local_cg->pos.y = param_1->pos[2] + -24.0 + local_cg->pos.y;
	if (EV_CheckCansel() != 0)
	{
		*(unsigned char *)param_1 = 4;
	}
}

// STUB: SADX 0x008baee0
static void Draw(struct task *tp)
{
}

// FUNCTION: SADX 0x008bb170
void FUN_008bb170(int param_1)
{
	*(float *)(param_1 + 0x10) = njSin((*(int *)(param_1 + 8) + 0x320) << 8) * 4.0;
}

// FUNCTION: SADX 0x008bb1a0
void FUN_008bb1a0(void *param_1)
{
	*(int *)((char *)param_1 + 0x1c) = (int)(njCos((*(int *)((char *)param_1 + 8) + 0x7d0) * 0xc8) * 4096.0);
}

// FUNCTION: SADX 0x008bb1e0
void BaloonScale(struct taskwk *twp)
{
	twp->scl.x = 1.0f - njCos(twp->counter.l << 0xb) * 0.05000000074505806;
	twp->scl.y = 1.0f - njSin(twp->counter.l << 0xb) * 0.05000000074505806;
}
