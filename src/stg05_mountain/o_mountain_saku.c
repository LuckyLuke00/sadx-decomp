#include "decls.h"
extern struct CCL_INFO object_rouya_info[2];
extern struct obj object_saku_saku_saku[1];
extern struct CCL_INFO object_saku2_info[1];
extern struct NJS_TEXLIST texlist_obj_mountain;

// FUNCTION: SADX 0x0082c7b0
void ObjectMountainSaku(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_mt_sotosaku_sotosaku;
	var1->value.ptr = &texlist_obj_mountain;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, object_saku_info, 1, 4);
		CheckCollisionScale(var1);
	}
	ObjectScaleCCollision(tp);
}

// FUNCTION: SADX 0x0082c800
void ObjectMountainSakusaku(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = &object_saku_saku_saku;
	var1->value.ptr = &texlist_obj_mountain;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)&object_saku2_info, 3, 4);
		CheckCollisionScale(var1);
	}
	ObjectCCollision_setMeshNWZ(tp);
	ObjectScaleCCollision(tp);
}

// FUNCTION: SADX 0x0082c850
void ObjectMountainRouya(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_royasaku_royasaku_royasaku;
	var1->value.ptr = &texlist_obj_mountain;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, object_rouya_info, 1, 4);
		CheckCollisionScale(var1);
	}
	ObjectScaleCCollision(tp);
}

// FUNCTION: SADX 0x0082c8a0
void ObjectMountainSotoSaku(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	*(void **)((char *)var1 + 8) = object_mt_sotosaku_sotosaku;
	var1->value.ptr = &texlist_obj_mountain;
	ObjectScaleNormal(tp);
}

// STUB: SADX 0x0082c8c0
void ObjectMountainTreeBox(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_mt_mtasiba_mtasiba;
	var1->value.ptr = &texlist_obj_mountain;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, (struct CCL_INFO *)0x03fea6b0, 1, 4);
		CheckCollisionScale(var1);
	}
	ObjectScaleCCollision(tp);
}

// FUNCTION: SADX 0x0082c910
void ObjectMountainTsaku(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_sotosaku_qsaku_qsaku;
	var1->value.ptr = &texlist_obj_mountain;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_rouya_info[1], 1, 4);
		CheckCollisionScale(var1);
	}
	ObjectScaleCCollision(tp);
}
