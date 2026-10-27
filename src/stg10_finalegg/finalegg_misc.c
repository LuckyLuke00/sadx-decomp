#include "decls.h"
extern struct fe_dynamicswk default_dynamicswk;

// STUB: SADX 0x008a1f70
void FEGG_SetBrokenPiece(struct taskwk *twp, struct NJS_MODEL *model)
{
}

// FUNCTION: SADX 0x008a1ff0
void FEGG_DrawBrokenPiece(struct taskwk *twp)
{
	struct NJS_MODEL *var1;
	struct task *var2;

	var1 = (struct NJS_MODEL *)twp->value.ptr;
	if (var1 != 0)
	{
		var2 = (struct task *)twp->counter.ptr;
		if (var2 != 0)
		{
			var1->mats = (struct NJS_MATERIAL *)var2;
			ds_DrawModelClip(var1, 1.0f);
		}
	}
}

// FUNCTION: SADX 0x008a2020
void FEGG_TaskActGravity(struct taskwk *twp, struct motionwk *mwp)
{
	mwp->acc.y -= 0.07999999821186066f;
}

// STUB: SADX 0x008a2040
void FEGG_TaskMove(struct taskwk *twp, struct motionwk *mwp)
{
}

// STUB: SADX 0x008a2110
void FEGG_TaskActBounce(struct taskwk *twp, struct motionwk *mwp)
{
}

// FUNCTION: SADX 0x008a2130
void FEGG_TaskCheckGround(struct taskwk *twp, struct motionwk *mwp)
{
	twp->flag &= 0xfffe;
	if (twp->pos.y < mwp->height)
	{
		twp->pos.y = mwp->height + 0.10000000149011612;
		twp->flag |= 1;
	}
}

// FUNCTION: SADX 0x008a2170
void FEGG_SetDynamicsWork(struct task *tp, struct fe_dynamicswk *dwp)
{
	struct fe_dynamicswk **var1;

	var1 = (struct fe_dynamicswk **)tp->mwp;
	if (dwp == NULL)
	{
		*var1 = &default_dynamicswk;
	}
	else
	{
		*var1 = dwp;
	}
}
