#include "decls.h"
void FUN_00501770(struct taskwk *param_1);
void FUN_00422560(int param_1);
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

// STUB: SADX 0x004ff9a0
long ObjectMovableInitialize(struct taskwk *twp, struct motionwk *mwp, unsigned long mode)
{
	return (long)0;
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

// FUNCTION: SADX 0x005003a0
void OConvertVector_O2G(struct taskwk *twp, struct NJS_POINT3 *vp)
{
	struct NJS_POINT3 v;

	v.x = vp->x;
	v.y = vp->y;
	v.z = vp->z;
	njPushMatrix(_nj_unit_matrix_);
	if (twp->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)twp->ang.z);
	}
	if (twp->ang.x != 0)
	{
		njRotateX(0, twp->ang.x);
	}
	if (twp->ang.y != 0)
	{
		njRotateY(0, twp->ang.y);
	}
	njCalcVector(0, &v, vp);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00500460
void InitObjects()
{
	struct task *local_8g;
	struct task *local_cg;

	DAT_05cc25a4 = NULL;
	DAT_05cc25a8 = 0;
	local_8g = (struct task *)CAlloc(1, 0x34);
	if (local_8g == NULL)
	{
		return;
	}
	DAT_05cc25a4 = local_8g;
	DAT_05cc25a8 = (int)local_8g;
	local_8g->next = (struct task *)0x1f;
	local_8g->awp = NULL;
	local_8g->thp = NULL;
	local_8g->last = NULL;
	local_cg = CreateElementalTask(0, 3, DrawObjects);
	if (local_cg != NULL)
	{
		local_cg->dest = EndDrawObjects;
		local_cg->disp = DrawObjects;
	}
	ReviveSetObject();
	InitJumpPanel();
	ClrRocketTaskWorkBuff();
	InitReleaseBox();
	InitialDynamite();
	ClearAllSwitches();
	InitItemBoxManager();
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

// FUNCTION: SADX 0x005005d0
void occ_DrawObject(struct taskwk *twp, struct obj *o, float clipScl)
{
	if (twp != NULL)
	{
		if ((twp->flag & 0x2000) != 0)
		{
			if ((twp->flag & 0x8000) != 0)
			{
				late_DrawObjectClipMesh(o, 0, clipScl);
			}
			else
			{
				late_DrawObjectClipMesh(o, 1, clipScl);
			}
		}
		else if ((twp->flag & 0x8000) != 0)
		{
			late_DrawObjectClipEx(o, 0, clipScl);
		}
		else if ((twp->flag & 0x4000) != 0)
		{
			late_DrawObjectClipEx(o, 1, clipScl);
		}
		else
		{
			ds_DrawObjectClip(o, clipScl);
		}
	}
	else
	{
		ds_DrawObjectClip(o, clipScl);
	}
}

// FUNCTION: SADX 0x005006a0
long ObjectNormal(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return 1;
	}
	if (CheckObjectTexture() != 0)
	{
		local_8->value.l = 0;
	}
	else
	{
		NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.l);
	}
	if (CheckObjectTexture() != 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			tp->exec = ObjectNormalDisplay;
			tp->disp = ObjectNormalDisplay;
			tp->dest = ObjectNormalExit;
		}
	}
	ObjectNormalDisplay(tp);
	return 0;
}

// FUNCTION: SADX 0x00500740
long ObjectNormal_LE(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return 1;
	}
	if (CheckObjectTexture() != 0)
	{
		local_8->value.l = 0;
	}
	else
	{
		NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.l);
	}
	if (CheckObjectTexture() != 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			tp->exec = ObjectNormalDisplay_LE;
			tp->disp = ObjectNormalDisplay_LE;
			tp->dest = ObjectNormalExit;
		}
	}
	ObjectNormalDisplay_LE(tp);
	return 0;
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

// FUNCTION: SADX 0x00500810
void ObjectNormalDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (SetObjectTexture() == 0)
	{
		___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	}
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njPushMatrix(NULL);
	njTranslateV(NULL, &local_8->pos);
	if (local_8->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)local_8->ang.z);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)local_8->ang.x);
	}
	if (local_8->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)local_8->ang.y);
	}
	occ_DrawObject(local_8, (struct obj *)local_8->counter.ptr, 1.0f);
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
}

// FUNCTION: SADX 0x00500920
void ObjectNormalDisplay_LE(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (SetObjectTexture() == 0)
	{
		___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	}
	FUN_00422560(3);
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njPushMatrix(NULL);
	njTranslateV(NULL, &local_8->pos);
	if (local_8->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)local_8->ang.z);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)local_8->ang.x);
	}
	if (local_8->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)local_8->ang.y);
	}
	occ_DrawObject(local_8, (struct obj *)local_8->counter.ptr, 1.0f);
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
	npSetZCompare();
}

// FUNCTION: SADX 0x00500a40
long ObjectScaleNormal(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return 1;
	}
	if (CheckObjectTexture() != 0)
	{
		local_8->value.l = 0;
	}
	else
	{
		NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.l);
	}
	if (CheckObjectTexture() != 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			tp->exec = ObjectScaleDisplay;
			tp->disp = ObjectScaleDisplay;
			tp->dest = ObjectNormalExit;
		}
	}
	ObjectScaleDisplay(tp);
	return 0;
}

// STUB: SADX 0x00500ae0
void ObjectScaleDisplay(struct task *tp)
{
}

// STUB: SADX 0x00500c70
float FUN_00500c70(float param_1, float param_2, float param_3)
{
	return (float)0;
}

// FUNCTION: SADX 0x00500d30
long ObjectCCollision(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return 1;
	}
	if (CheckObjectTexture() != 0)
	{
		local_8->value.l = 0;
	}
	else
	{
		NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.l);
	}
	if (CheckObjectTexture() != 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			tp->dest = ObjectNormalExit;
			tp->exec = ObjectCCollisionExecute;
			tp->disp = ObjectNormalDisplay;
		}
	}
	ObjectNormalDisplay(tp);
	return 0;
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

// FUNCTION: SADX 0x00500e40
long ObjectCCollision_L(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut_L(tp) != 0)
	{
		return 1;
	}
	if (CheckObjectTexture() != 0)
	{
		local_8->value.l = 0;
	}
	else
	{
		NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	}
	if (CheckObjectTexture() != 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			tp->dest = ObjectNormalExit;
			tp->exec = ObjectCCollisionExecute_L;
			tp->disp = ObjectNormalDisplay;
		}
	}
	ObjectNormalDisplay(tp);
	return 0;
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

// FUNCTION: SADX 0x00500f50
long ObjectScaleCCollision(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return 1;
	}
	if (CheckObjectTexture() != 0)
	{
		local_8->value.l = 0;
	}
	else
	{
		NeonuLoadTexture((struct NJS_TEXLIST *)local_8->value.l);
	}
	if (CheckObjectTexture() != 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			tp->dest = ObjectNormalExit;
			tp->exec = ObjectScaleCCollisionExecute;
			tp->disp = ObjectScaleDisplay;
		}
	}
	ObjectScaleDisplay(tp);
	return 0;
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

// FUNCTION: SADX 0x005012a0
int FUN_005012a0(struct task *param_1)
{
	struct task *local_8;
	if (DAT_05cc25a4 == 0)
	{
		return 0;
	}
	local_8 = (struct task *)MAlloc(0x34);
	if (local_8 == 0)
	{
		return 0;
	}
	*local_8 = *param_1->ptp;
	FUN_00501300(param_1, local_8);
	return 1;
}

// FUNCTION: SADX 0x00501300
void FUN_00501300(struct task *param_1, struct task *param_2)
{
	if (DAT_05cc25a4->awp == 0)
	{
		DAT_05cc25a4->awp = (struct anywk *)param_2;
		DAT_05cc25a4->next = (struct task *)((long)DAT_05cc25a4->next & 0xffffffef);
	}
	else
	{
		((struct task *)DAT_05cc25a8)->thp = param_2;
	}
	param_1->ctp = param_2;
	DAT_05cc25a8 = (int)param_2;
}

// FUNCTION: SADX 0x00501350
void ObjectGCollisionExecute(struct task *tp)
{
	struct taskwk *local_8g;
	struct OBJ_CONDITION *local_cg;

	local_8g = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	local_cg = (struct OBJ_CONDITION *)local_8g->counter.l;
	if (local_cg != NULL)
	{
		*(float *)((char *)local_cg + 8) = local_8g->pos.x;
		*(float *)((char *)local_cg + 0xc) = local_8g->pos.y;
		*(float *)((char *)local_cg + 0x10) = local_8g->pos.z;
		*(long *)((char *)local_cg + 0x14) = local_8g->ang.x;
		*(long *)((char *)local_cg + 0x18) = local_8g->ang.y;
		*(long *)((char *)local_cg + 0x1c) = local_8g->ang.z;
		if (CheckCollisionP(&local_8g->pos, *(float *)((char *)*(void **)((char *)local_cg + 4) + 0x24) + 16.0f) != 0)
		{
			local_8g->flag |= 0x100;
		}
		else
		{
			local_8g->flag &= ~0x100;
		}
	}
	if (tp->dest == ObjectGCollisionExit)
	{
		ObjectGCollisionDisplay(tp);
	}
}

// FUNCTION: SADX 0x00501440
void ObjectGCollisionDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (SetObjectTexture() == 0)
	{
		___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	}
	njPushMatrix(NULL);
	njTranslateV(NULL, &local_8->pos);
	if (local_8->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)local_8->ang.z);
	}
	if (local_8->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)local_8->ang.y);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)local_8->ang.x);
	}
	occ_DrawObject(local_8, (struct obj *)local_8->counter.ptr, 1.0f);
	njPopMatrix(1);
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

// FUNCTION: SADX 0x00501680
void ObjectGCollisionExecute___Mesh(struct task *tp)
{
	struct taskwk *local_8g;
	struct OBJ_CONDITION *local_cg;

	local_8g = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	local_cg = (struct OBJ_CONDITION *)local_8g->counter.l;
	if (local_cg != NULL)
	{
		*(float *)((char *)local_cg + 8) = local_8g->pos.x;
		*(float *)((char *)local_cg + 0xc) = local_8g->pos.y;
		*(float *)((char *)local_cg + 0x10) = local_8g->pos.z;
		*(long *)((char *)local_cg + 0x14) = local_8g->ang.x;
		*(long *)((char *)local_cg + 0x18) = local_8g->ang.y;
		*(long *)((char *)local_cg + 0x1c) = local_8g->ang.z;
		if (CheckCollisionP(&local_8g->pos, *(float *)((char *)*(void **)((char *)local_cg + 4) + 0x24) + 16.0f) != 0)
		{
			local_8g->flag |= 0x100;
		}
		else
		{
			local_8g->flag &= ~0x100;
		}
	}
	if (tp->dest == ObjectGCollisionExit)
	{
		FUN_00501770((struct taskwk *)tp);
	}
}

// STUB: SADX 0x005017c0
void CheckCollisionScale(struct taskwk *twp)
{
}

// STUB: SADX 0x00501910
struct obj *SetModelCollision(struct obj *OriginalObj, struct task *tp, long Flag)
{
	return (struct obj *)0;
}
