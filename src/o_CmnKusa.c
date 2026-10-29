#include "decls.h"
void FUN_008bbd00(struct task *param_1, struct taskwk *param_2, struct forcewk *param_3);
void FUN_008bbea0(struct taskwk *param_1, struct forcewk *param_2);
extern int DAT_05b9d838;

// STUB: SADX 0x008bb9b0
void ObjectCmnKusa(struct task *tp)
{
}

// FUNCTION: SADX 0x008bbba0
void NomalObject(struct task *tp)
{
	void (*local_8)(struct task *);
	local_8 = tp->disp;
	local_8(tp);
	CheckRangeOut(tp);
}

// STUB: SADX 0x008bbbd0
void CmnKusaParts(struct task *tp)
{
}

// STUB: SADX 0x008bbd00
void FUN_008bbd00(struct task *param_1, struct taskwk *param_2, struct forcewk *param_3)
{
}

// STUB: SADX 0x008bbea0
void FUN_008bbea0(struct taskwk *param_1, struct forcewk *param_2)
{
}

// FUNCTION: SADX 0x008bbfc0
void FUN_008bbfc0(struct task *param_1)
{
	long local_8;
	local_8 = ChkItemInPercent(CmnKusaRanItemTbl);
	if (local_8 == 0)
	{
		return;
	}
	MakePopUpItem((struct taskwk *)param_1, local_8);
}

// FUNCTION: SADX 0x008bbff0
void DrawCmnKusa(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (dsCheckViewV(&local_8->pos, 10.0f) == 0)
	{
		return;
	}
	___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, local_8->ang.y);
	late_DrawObjectMesh((struct obj *)local_8->counter.ptr, 0);
	njPopMatrix(1);
}

// STUB: SADX 0x008bc0d0
void DrawCmnKusaParts(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (dsCheckViewV(&local_8->pos, 10.0f) == 0)
	{
		return;
	}
	___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, local_8->ang.y);
	SaveConstantAttr();
	OnConstantAttr(0, 0x100000);
	SetMaterial(*(float *)&local_8->timer, 0.0f, 0.0f, 0.0f);
	late_DrawModelMesh((struct NJS_MODEL *)*(void **)((char *)local_8->counter.ptr + 4), 0);
	ResetMaterial();
	LoadConstantAttr();
	njPopMatrix(1);
}
