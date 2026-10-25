#include "decls.h"
extern short DAT_060dfc80;
extern int DAT_04c37b48[6][3];

// STUB: SADX 0x008c74a0
int traceObjectTree(struct obj *obj, struct obj **list)
{
	return (int)0;
}

// STUB: SADX 0x008c75b0
void initialChaos(struct taskwk *twp, struct chaoswk *chwp, int id)
{
}

// STUB: SADX 0x008c76f0
void InitialChaosPos(struct taskwk *twp)
{
}

// STUB: SADX 0x008c7e10
void CalcChaosObjectPos(struct taskwk *twp, struct CHAOS_OBJPVTBL *tbl, float yofs)
{
}

// FUNCTION: SADX 0x008c7fd0
struct task *CreateTaskSetPos(int level, void (*func)(struct task *), struct task *tp, struct NJS_POINT3 *offset)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, level, func);
	if (local_8 != 0)
	{
		local_8->twp->pos = tp->twp->pos;
		if (offset != 0)
		{
			njAddVector(&tp->twp->pos, offset);
		}
	}
	return local_8;
}

// FUNCTION: SADX 0x008c8040
struct task *CreateChildTaskSetPos(unsigned short im, void *func, struct task *tp, struct NJS_POINT3 *offset)
{
	struct task *local_8;
	local_8 = CreateChildTask(im, (void (*)(struct task *))func, tp);
	if (local_8 != 0)
	{
		local_8->twp->pos = tp->twp->pos;
		if (offset != 0)
		{
			njAddVector(&tp->twp->pos, offset);
		}
	}
	return local_8;
}

// FUNCTION: SADX 0x008c80b0
void ChaosSurfacePatternChange(struct chaoswk *chwp)
{
	int local_8;
	local_8 = (int)chwp->texlist->textures + DAT_060dfc80 * 0xc;
	chwp->txchg_tmr++;
	if (chwp->txchg_tmr >= 4)
	{
		chwp->txchg_tmr = 0;
		chwp->txchg_num++;
		if (chwp->txchg_num >= 6)
			chwp->txchg_num = 0;
	}
	*(int *)((char *)local_8 + 8) = *(int *)((char *)DAT_04c37b48 + chwp->txchg_num * 0xc);
}

// STUB: SADX 0x008c8130
void ChaosHeadColorChange(struct obj *obj)
{
}

// FUNCTION: SADX 0x008c81e0
struct task *SetCircleLimit(struct NJS_POINT3 *pos, struct NJS_POINT3 *center, float radius)
{
	struct task *local_cg;
	struct taskwk *local_8g;
	local_cg = CreateElementalTask(2, 0, CircleLimit);
	if (local_cg != 0) {
		local_8g = local_cg->twp;
		local_8g->pos = *center;
		local_8g->scl.x = radius;
		*(void **)((char *)local_8g + 8) = (void *)pos;
	}
	return local_cg;
}

// STUB: SADX 0x008c8240
void CircleLimit(struct task *tp)
{
}

// FUNCTION: SADX 0x008c83c0
void ResetRenderingParameter()
{
	njControl3D(0x36c);
	njSetConstantAttr(-1, 0x2000);
	ResetMaterial();
}
