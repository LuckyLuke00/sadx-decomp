#include "decls.h"
void FUN_005ff920(struct task *param_1, struct ModeSelPrmType *param_2);
void FUN_005ff9b0(struct anywk *param_1);
void FUN_005ff970(struct anywk *param_1);
void FUN_005ff920(struct task *param_1, struct ModeSelPrmType *param_2);
extern struct task *DAT_05edd9ac;

// FUNCTION: SADX 0x005ff8b0
struct task *SetAdvaEmblemViewTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, emblem_view_exec);
	DAT_05edd9ac = local_8g;
	if (DAT_05edd9ac)
	{
		local_cg = CAlloc(1, 0x3c);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005ff920(local_8g, prmp);
		local_8g->exec = emblem_view_exec;
		local_8g->disp = emblem_view_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005ff920
void FUN_005ff920(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	*(void **)((char *)local_8 + 4) = *(void **)param_2;
	*(void **)((char *)local_8 + 8) = *(void **)((char *)param_2 + 4);
	*(float *)((char *)local_8 + 0xc) = 5800.0f;
	*(int *)((char *)local_8 + 0) = 0;
	FUN_005ff970(local_8);
}

// FUNCTION: SADX 0x005ff970
void FUN_005ff970(struct anywk *param_1)
{
	FUN_005ff9b0(param_1);
	*(int *)((char *)param_1 + 0x18) = 0;
	*(int *)((char *)param_1 + 0x34) = 0;
	*(float *)((char *)param_1 + 0x2c) = 1.0f;
	*(unsigned char *)((char *)param_1 + 0x39) = 0xff;
}

// STUB: SADX 0x005ff9b0
void FUN_005ff9b0(struct anywk *param_1)
{
}

// FUNCTION: SADX 0x005ffba0
void FUN_005ffba0(struct anywk *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_EMBLEMVIEW);
	SetAdvaModeBGM((enum AvaBgmEnum)4);
	FUN_005ff970(param_1);
	*(unsigned char *)((char *)param_1 + 0x3a) = 0;
	*(float *)((char *)param_1 + 0x30) = 0.0f;
	*(unsigned char *)((char *)param_1 + 0x3b) = 0;
}

// STUB: SADX 0x005ffbe0
void emblem_view_sub_exec(struct EmblemViewWk *wkp)
{
}

// FUNCTION: SADX 0x005ffde0
void emblem_view_disp(struct task *tp)
{
	struct EmblemViewWk *local_8;

	local_8 = (struct EmblemViewWk *)tp->awp;
	if (!local_8->BaseCol)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawSkyBg(local_8->BaseZ + -2.0);
	DrawEmblemViewBg(local_8);
	DrawEmblemViewChar(local_8);
	DrawEmblemViewHead(local_8);
	DrawEmblemViewEmblem(local_8);
}

// STUB: SADX 0x00600590
void DrawEmblemViewHead(struct EmblemViewWk *wkp)
{
}

// FUNCTION: SADX 0x006009a0
void DrawEmblemViewBg(struct EmblemViewWk *wkp)
{
	ghSetPvrTexMaterial(-1);
	___njSetTexture(&texlist_ava_emblemview);
	DrawTitleBack(0.0f * ScreenRaitoX, ScreenRaitoY * 32.0f, wkp->BaseZ + -8.0f, ScreenRaitoX * 565.0f, ScreenRaitoY * 42.0f);
	ghDrawPvrTextureS(0, ScreenRaitoX * 32.0f, ScreenRaitoY * 42.0f, wkp->BaseZ + -14.0f, ScreenRaitoX, ScreenRaitoY);
}

// FUNCTION: SADX 0x00600aa0
void FreeAdvaEmblemViewTask()
{
	if (DAT_05edd9ac)
	{
		DestroyTask(DAT_05edd9ac);
	}
}
