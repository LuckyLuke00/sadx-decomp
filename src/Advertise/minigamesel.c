#include "decls.h"
extern unsigned char DAT_05cd14ed;
extern struct task *DAT_05edd9b0;

// STUB: SADX 0x00600e90
struct task *FUN_00600e90(struct ModeSelPrmType *param_1)
{
	return (struct task *)0;
}

// STUB: SADX 0x00600f10
struct task *SetAdvaMiniGameSelTask(struct ModeSelPrmType *prmp, struct task *src)
{
	return (struct task *)0;
}

// STUB: SADX 0x00600fc0
void FUN_00600fc0(void *param_1)
{
}

// FUNCTION: SADX 0x006011c0
void FUN_006011c0(void *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_MINIGAME_SEL);
	SetAdvaModeBGM((enum AvaBgmEnum)4);
	SetAdvaSerifu((enum AvaSerifuModeEnum)4);
	DAT_05cd14e1 = 1;
	FUN_00600f70(param_1);
	*(char *)((char *)param_1 + 0xcd) = 0;
	*(char *)((char *)param_1 + 0xce) = 0;
}

// FUNCTION: SADX 0x00601890
void minigame_sel_disp(struct task *tp)
{
	struct MiniGameSelWk *local_8;

	local_8 = (struct MiniGameSelWk *)tp->awp;
	if (!local_8->BaseCol)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawSkyBg(local_8->BaseZ + -2.0);
	DrawMiniGameSelBg(local_8);
	FUN_00601cf0(local_8);
	DrawBCharName((enum AvaCharEnum)DAT_05cd14ed, 0xffffffff, 158.0f, 90.0f, local_8->BaseZ + -14.0);
	DrawMiniGameSelStage(local_8);
}

// STUB: SADX 0x00601c90
int now_emblem_stg(struct MiniGameSelWk *wkp)
{
	return (int)0;
}

// FUNCTION: SADX 0x00601cf0
void FUN_00601cf0(struct MiniGameSelWk *param_1)
{
	DrawMiniGameSelEmblem(param_1);
	DrawMiniGameSelRank123(param_1);
}

// STUB: SADX 0x00601d10
void DrawMiniGameSelEmblem(struct MiniGameSelWk *wkp)
{
}

// FUNCTION: SADX 0x00602340
void FreeAdvaMiniGameSelTask()
{
	if (DAT_05edd9b0)
	{
		DestroyTask(DAT_05edd9b0);
	}
}
