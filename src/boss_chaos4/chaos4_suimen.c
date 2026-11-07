#include "decls.h"
extern float DAT_060c2158;
extern char DAT_060c2160;
extern int DAT_060c214c;
extern float DAT_060c2154;
extern struct NJS_TEXNAME texture_chaos4_numa[12];
extern struct NJS_TEXLIST texlist_chaos4_numa;
extern struct NJS_TEXLIST texlist_numa_f;
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void ___njSetConstantMaterial(struct NJS_ARGB *argb);
void ResetMaterial();
struct NJS_POINT3;
extern int DAT_05b9d838;
struct SuimenTask;
struct task;
struct obj;
void RegisterCollisionEntry(long slAttribute, struct task *pTask, struct obj *pObject);
struct obj *GetMobileLandObject();
void C4PondObjCreate(struct SuimenTask *st, struct task *pTask);

// STUB: SADX 0x006f0390
void C4PondObjCreate(struct SuimenTask *st, struct task *pTask)
{
}

// STUB: SADX 0x006f05f0
void FUN_006f05f0(float *param_1)
{
}

// FUNCTION: SADX 0x006f0680
void Dsp_SuimenYurashi(struct task *pTask)
{
	struct anywk *var1;
	struct taskwk *var2;

	var1 = pTask->awp;
	var2 = pTask->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (DAT_060c2158 > -1.0f)
	{
		*(float *)((char *)var1 + 0x154) = DAT_060c2158;
		*(float *)((char *)var1 + 0x158) = 0.0f;
		*(float *)((char *)var1 + 0x15c) = 0.0f;
		*(float *)((char *)var1 + 0x160) = 0.0f;
		___njSetConstantMaterial((struct NJS_ARGB *)((char *)var1 + 0x154));
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 0xa);
		___njSetTexture(&texlist_chaos4_object);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var2->pos);
		if (DAT_05b3df4c != 0)
		{
			DAT_05b3df40 = -17952.0f;
		}
		late_DrawObjectClipMesh((struct obj *)var1->work.ptr[1], 0, 1.0f);
		DAT_05b3df40 = 0.0f;
		njPopMatrix(1);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		ResetMaterial();
		DAT_060c2160 = 1;
	}
}

// STUB: SADX 0x006f0770
void End_SuimenYurashi(struct task *pTask)
{
}

// STUB: SADX 0x006f07e0
void C4HamonMake(struct NJS_POINT3 *pos)
{
}

// FUNCTION: SADX 0x006f0830
void Dsp_first_pond(struct task *pTask)
{
	struct NJS_ARGB argb;

	if (DAT_060c2154 > -1.0f)
	{
		if (DAT_05b9d838 == 0)
		{
			___njSetTexture(&texlist_numa_f);
			argb.a = DAT_060c2154;
			argb.b = 0.0f;
			argb.g = 0.0f;
			argb.r = 0.0f;
			___njSetConstantMaterial(&argb);
			ResetMaterial();
		}
	}
}

// FUNCTION: SADX 0x006f0a20
void Exe_side_collision(struct task *pTask)
{
	if (DAT_05baf368[0]->pos.y < 0.0f)
	{
		ADX_Close();
		KillHimByFallingDownP(0);
	}
}

// FUNCTION: SADX 0x006f0a50
void End_side_collision(struct task *pTask)
{
	ReleaseMobileLandObject((struct obj *)pTask->awp);
	pTask->awp = NULL;
}

// STUB: SADX 0x006f0a70
void Exe_SuimenYurashi(struct task *pTask)
{
}

// FUNCTION: SADX 0x006f0b30
void FUN_006f0b30()
{
	struct NJS_ARGB local_18;

	if (DAT_060c2154 > -1.0f)
	{
		if (DAT_05b9d838 == 0)
		{
			___njSetTexture(&texlist_numa_f);
			local_18.a = DAT_060c2154;
			local_18.b = 0.0f;
			local_18.g = 0.0f;
			local_18.r = 0.0f;
			___njSetConstantMaterial(&local_18);
			ResetMaterial();
		}
	}
	if (DAT_05b9d838 == 0)
	{
		texlist_numa_f.textures = &texture_chaos4_numa[DAT_060c214c];
		DAT_060c214c++;
		if ((unsigned int)DAT_060c214c >= texlist_chaos4_numa.nbTexture)
		{
			DAT_060c214c = 0;
		}
	}
}

// FUNCTION: SADX 0x006f0be0
void Chaos4SuimenChange(long inorder)
{
	struct task *local_4;
	struct taskwk *local_8;

	local_4 = CreateElementalTask(2, 3, Exe_suimen_change);
	if (local_4 != NULL)
	{
		local_8 = local_4->twp;
		EnemyInitialize(local_4, local_8);
		local_8->timer.l = 0x1e;
		local_8->counter.l = inorder;
		local_4->exec = Exe_suimen_change;
	}
}

// FUNCTION: SADX 0x006f0c20
void Chaos4SideCollisionSet()
{
	struct task *local_8;
	struct obj *local_4;

	local_8 = CreateElementalTask(6, 3, Exe_side_collision);
	if (local_8 != 0)
	{
		EnemyInitialize(local_8, local_8->twp);
		local_4 = GetMobileLandObject();
		*(struct obj *)local_4 = object_c4_ar_s_kabeb_ar_s_kabeb[0];
		local_4->evalflags &= 0xfffffffc;
		local_8->awp = (struct anywk *)local_4;
		local_8->twp->flag |= 0x100;
		RegisterCollisionEntry(0x20200001, local_8, local_4);
		local_8->exec = Exe_side_collision;
		local_8->dest = End_side_collision;
	}
}
