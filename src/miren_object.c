#include "decls.h"
void FUN_005720e0(struct obj *param_1, float param_2);
extern struct Angle3 DAT_00962c74;
void FUN_005720e0(struct obj *param_1, float param_2);
extern int DAT_05b9d838;
void FUN_00572100(struct NJS_TEXLIST *param_1);
void FUN_00573040(int param_1);
void FUN_008c2030(int param_1);
void FUN_00571b20(int param_1);

// STUB: SADX 0x00571ac0
void MirenObjInitCharColli(struct task *task_p, const struct ObjectInfo *objInfo_p, const struct ObjCmnInfo *cmnInfo_p)
{
}

// FUNCTION: SADX 0x00571af0
void FUN_00571af0(int param_1)
{
	FUN_00573040(param_1);
	FUN_008c2030(param_1);
	FUN_00571b20(param_1);
}

// FUNCTION: SADX 0x00571b20
void FUN_00571b20(int param_1)
{
	if (*(int *)((char *)param_1 + 4) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)param_1 + 4));
	}
	return;
}

// FUNCTION: SADX 0x00571b40
void MirenObjDrawCharColliObjectNoScale(struct obj *obj_p, struct taskwk *taskWk_p, struct NJS_TEXLIST *texList_p)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &taskWk_p->pos);
	FUN_00571af0((int)(&taskWk_p->ang));
	FUN_00572100(texList_p);
	___dsDrawObject(obj_p);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00571ba0
struct obj *MirenObjAllocMobileLandObject(const struct obj *orgObj_p)
{
	struct obj *local_8;

	local_8 = GetMobileLandObject();
	if (local_8 != 0)
	{
		local_8->evalflags = orgObj_p->evalflags & 0xfffffffc;
		local_8->model = orgObj_p->model;
		local_8->child = orgObj_p->child;
		local_8->sibling = orgObj_p->sibling;
		FUN_005720e0((struct obj *)((char *)local_8 + 0x20), 1.0f);
	}
	return local_8;
}

// STUB: SADX 0x00571c00
void MirenObjSetObjectMatrix(struct obj *obj_p, const struct taskwk *taskWk_p, float scale)
{
}

// FUNCTION: SADX 0x00571c50
void MirenObjClearForceWork(struct forcewk *forceWk_p)
{
	forceWk_p->ang_spd = DAT_00962c74;
	forceWk_p->pos_spd = *(struct NJS_POINT3 *)&DAT_00962c74;
}

// STUB: SADX 0x00571ca0
void MirenObjEntryMobileLandObject(struct task *task_p, struct obj *obj_p, long attr, float scale)
{
}

// STUB: SADX 0x00571d40
long MirenObjCheckCollisionP(struct taskwk *taskWk_p, float dist)
{
	return (long)0;
}

// FUNCTION: SADX 0x00571da0
void MirenObjDrawMobileLandObject(struct obj *obj_p, struct taskwk *taskWk_p, float scale, struct NJS_TEXLIST *texList_p)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &taskWk_p->pos);
	FUN_008dd760((int)(&taskWk_p->ang));
	FUN_005723e0(scale);
	FUN_00572100(texList_p);
	___dsDrawObject(obj_p);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00571e10
void MirenObjFreeMobileLandObject(struct task *task_p, struct obj *obj_p)
{
	if (obj_p != NULL)
	{
		WithdrawCollisionEntry(task_p, obj_p);
		ReleaseMobileLandObject(obj_p);
	}
}
