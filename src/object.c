#include "decls.h"
void FUN_005015e0(void *param_1);
void FUN_00501300(struct task *param_1, struct task *param_2);
extern int DAT_05b9d838;
extern struct task *DAT_05cc25a4;
extern int DAT_05cc25a8;

// FUNCTION: SADX 0x004ff920
void ObjectCCollision_setWZ(struct task *tp)
{
	tp->twp->flag |= 0x4000;
}

// FUNCTION: SADX 0x004ff940
void ObjectCCollision_setNWZ(struct task *tp)
{
	tp->twp->flag |= 0x8000;
}

// FUNCTION: SADX 0x004ff960
void ObjectCCollision_setMeshWZ(struct task *tp)
{
	tp->twp->flag |= 0x6000;
}

// FUNCTION: SADX 0x004ff980
void ObjectCCollision_setMeshNWZ(struct task *tp)
{
	tp->twp->flag |= 0xa000;
}

// FUNCTION: SADX 0x00500320
void ObjectSwingableRegularExecute(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	EntryColliList(local_cg);
	ObjectSetupInput(local_cg, local_8g);
}

// FUNCTION: SADX 0x00500360
void ObjectSetupInput(struct taskwk *twp, struct motionwk *mwp)
{
	twp->flag &= (short)0xffc7;
	if (mwp != 0)
	{
		mwp->acc.z = 0.0f;
		mwp->acc.y = 0.0f;
		mwp->acc.x = 0.0f;
	}
}

// FUNCTION: SADX 0x00500530
void EndDrawObjects(struct task *tp)
{
	struct task *local_8;

	DAT_05cc25a8 = 0;
	while (DAT_05cc25a4 != NULL)
	{
		local_8 = (struct task *)DAT_05cc25a4->awp;
		if (local_8 != NULL)
		{
			DAT_05cc25a4->awp = (struct anywk *)local_8->thp;
		}
		else
		{
			local_8 = DAT_05cc25a4;
			DAT_05cc25a4 = NULL;
		}
		Free(local_8);
	}
}

// FUNCTION: SADX 0x00500590
void DrawObjects(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838)
		return;
	SetObjectTexture();
	occ_DrawObject(local_8, (struct obj *)DAT_05cc25a4, 1.0f);
}

// FUNCTION: SADX 0x005007e0
void ObjectNormalExit(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (local_8->value.l != 0)
	{
		late_ReleaseTexture((NJS_TEXLIST *)local_8->value.l);
	}
}

// FUNCTION: SADX 0x00500dd0
void ObjectCCollisionExecute(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(local_8);
		ObjectSetupInput(local_8, NULL);
	}
	if (tp->dest == ObjectNormalExit)
	{
		ObjectNormalDisplay(tp);
	}
}

// FUNCTION: SADX 0x00500ee0
void ObjectCCollisionExecute_L(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut_L(tp) != 0)
	{
		return;
	}
	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(local_8);
		ObjectSetupInput(local_8, 0);
	}
	if (tp->dest == ObjectNormalExit)
	{
		ObjectNormalDisplay(tp);
	}
}

// FUNCTION: SADX 0x00500ff0
void ObjectScaleCCollisionExecute(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(local_8);
		ObjectSetupInput(local_8, NULL);
	}
	if (tp->dest == ObjectNormalExit)
	{
		ObjectScaleDisplay(tp);
	}
}

// STUB: SADX 0x005012a0
int FUN_005012a0(struct task *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00501300
void FUN_00501300(struct task *param_1, struct task *param_2)
{
	if (DAT_05cc25a4->awp == 0)
	{
		*(struct anywk **)&DAT_05cc25a4->awp = (struct anywk *)param_2;
		DAT_05cc25a4->next = (struct task *)((long)DAT_05cc25a4->next & 0xffffffef);
	}
	else
	{
		((struct task *)DAT_05cc25a8)->thp = param_2;
	}
	param_1->ctp = param_2;
	DAT_05cc25a8 = (int)param_2;
}

// FUNCTION: SADX 0x00501510
void ObjectGCollisionExit(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (local_8->value.ptr != 0)
	{
		late_ReleaseTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	}
	if (local_8->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)local_8->counter.ptr);
		ReleaseMobileLandObject((struct obj *)local_8->counter.ptr);
	}
}

// FUNCTION: SADX 0x00501570
void FUN_00501570(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	if (local_8->value.ptr != 0)
	{
		late_ReleaseTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	}
	if (local_8->counter.ptr != 0)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)local_8->counter.ptr);
		ReleaseMobileLandObject((struct obj *)local_8->counter.ptr);
	}
	FUN_005015e0(local_8->timer.ptr);
}
