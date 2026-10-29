#include "decls.h"
#include "../advertise.h"
extern float ScreenRaitoX;
extern float ScreenRaitoY;
struct FileSelWk;
void FUN_004ba980(void);
enum AvaCharEnum AvaGetlastPlayer();
extern void *DAT_05b42528;
void *_SOCMalloc(unsigned int param_1, const char *param_2, int param_3);
extern unsigned char DAT_025d4cad;

#pragma warning(disable: 4716)

void _SOCFree(void *param_1, const char *param_2, int param_3);
void FUN_004b6c50(struct FileSelWk *param_1);
void FUN_004b7800(struct FileSelWk *param_1);
void file_sel_disp(struct task *tp);
void FUN_004b9c10(struct FileSelWk *param_1);
void FUN_0041c2d0(void *param_1);

extern void *DAT_05cc3564;
extern unsigned char DAT_05cc3568;
extern unsigned char DAT_05cc3560;
extern unsigned char DAT_05cd14e9;
extern unsigned char DAT_05cd2604;
extern int DAT_05b9d848;
extern struct task *DAT_05cda18c;
extern unsigned char DAT_05b4252c;
extern unsigned char DAT_05b3e356;
extern struct task *DAT_05b42524;
extern struct task *DAT_05b42520;
extern struct task *DAT_05b42530;
extern Magic::RenderCore::Texture *DAT_05b3e378;
extern Magic::RenderCore::Texture *DAT_05b3e37c;

// STUB: SADX 0x004b6b50
void DrawFileDelDlgSub(struct DDlgType *dlgp)
{
}

// FUNCTION: SADX 0x004b6c50
void FUN_004b6c50(struct FileSelWk *param_1)
{
	param_1->SubMode = FILESEL_SMD_STAY;
	if (DAT_05cc3568)
	{
		DAT_05cd14e9 = DAT_05cc3560;
	}
	else
	{
		DAT_05cd14e9 = 0;
	}
	param_1->SelCh = AVA_SONIC;
	param_1->CsrAniAng = 0;
	param_1->CsrCol = 0xffff0000;
}

// FUNCTION: SADX 0x004b6ca0
void FUN_004b6ca0(void)
{
	if (DAT_05cc3564)
	{
		_SOCFree(DAT_05cc3564, "..\\..\\src\\Advertise\\filesel.cpp", 3091);
		DAT_05cc3564 = 0;
	}
}

// FUNCTION: SADX 0x004b6cd0
struct task *SetAdvaFileSelTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, file_sel_exec);
	DAT_05b42530 = local_8g;
	if (DAT_05b42530 != 0)
	{
		local_cg = CAlloc(1, 0x38);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_004b6d40(local_8g, prmp);
		local_8g->exec = file_sel_exec;
		local_8g->disp = file_sel_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x004b6d40
void FUN_004b6d40(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct FileSelWk *local_8;

	local_8 = (struct FileSelWk *)param_1->awp;
	local_8->PrevMode = *(enum AdvaModeEnum *)param_2;
	local_8->NextMode = *(enum AdvaModeEnum *)((char *)param_2 + 4);
	local_8->BaseZ = 5900.0f;
	local_8->Stat = ADVA_STAT_REQWAIT;
	FUN_004b6c50(local_8);
}

// FUNCTION: SADX 0x004b6d90
void file_sel_exec(struct task *tp)
{
	struct FileSelWk *local_8;

	local_8 = (struct FileSelWk *)tp->awp;
	if (*(int *)((char *)DAT_05cda18c->awp + 4) == 2 && local_8->Stat == ADVA_STAT_REQWAIT)
	{
		FileSelModeWakeProcedure(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEIN;
	}
	if (*(int *)((char *)DAT_05cda18c->awp + 8) == 2 && local_8->Stat == ADVA_STAT_KEEP)
	{
		FUN_004b7800(local_8);
		local_8->T = 0.0f;
		local_8->Stat = ADVA_STAT_FADEOUT;
	}
	switch (local_8->Stat)
	{
	case ADVA_STAT_REQWAIT:
		local_8->BaseCol = 0;
		break;
	case ADVA_STAT_FADEIN:
		local_8->BaseCol = GetFadeInColFromT(local_8->T);
		local_8->T = (float)(DAT_05b9d848 * 0.05) + local_8->T;
		if (local_8->T >= 1.0)
		{
			CloseDialog();
			local_8->Stat = ADVA_STAT_KEEP;
		}
		DAT_05cd2604 = 1;
		break;
	case ADVA_STAT_KEEP:
		local_8->BaseCol = -1;
		*(int *)((char *)DAT_05cda18c->awp + 0xc) = 2;
		file_sel_sub_exec(local_8);
		break;
	case ADVA_STAT_FADEOUT:
		local_8->BaseCol = GetFadeOutColFromT(local_8->T);
		local_8->T = (float)(DAT_05b9d848 * 0.05) + local_8->T;
		if (local_8->T > 1.0)
		{
			local_8->T = 1.0f;
		}
		if (local_8->T >= 1.0)
		{
			AvaReleaseTexForEachMode(ADVA_MODE_FILE_SEL);
			ghReleaseFontTexture(Ascii16x16FontInfo);
			*((unsigned char *)DAT_05cda18c->awp + 0x1f) = 1;
			local_8->Stat = ADVA_STAT_REQWAIT;
			ReleaseLineList();
		}
		break;
	}
}

// FUNCTION: SADX 0x004b7800
void FUN_004b7800(struct FileSelWk *param_1)
{
	if (DAT_05b3e378)
	{
		FUN_0041c2d0(DAT_05b3e378);
		delete DAT_05b3e378;
		DAT_05b3e378 = 0;
	}
	if (DAT_05b3e37c)
	{
		FUN_0041c2d0(DAT_05b3e37c);
		delete DAT_05b3e37c;
		DAT_05b3e37c = 0;
	}
}

// FUNCTION: SADX 0x004b83c0
void file_sel_disp(struct task *tp)
{
	struct FileSelWk *local_8;

	local_8 = (struct FileSelWk *)tp->awp;
	if (local_8->BaseCol == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	local_8->OfsX = 20.0f;
	DrawSkyBg(local_8->BaseZ + -2.0);
	FUN_004b9c10(local_8);
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawFileSelScoreWindow(local_8);
	DrawFileSelBallChar(local_8);
	DrawFileSelCsr(local_8);
	DrawFileSelBg(local_8);
	DrawFileEmblem(local_8);
	FUN_004b9330((struct task *)local_8);
	DrawStartChiten(local_8);
	DrawSaishuuClear(local_8);
	DrawPlayTime(local_8);
	if (DAT_05b4252c)
	{
		AlertWindowTask(DAT_05b42524);
	}
	if (DAT_05b3e356)
	{
		AlertWindowTask(DAT_05b42520);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x004b84d0
void DrawStartChiten(struct FileSelWk *wkp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x004b85b0
void DrawSaishuuClear(struct FileSelWk *wkp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x004b8710
void DrawPlayTime(struct FileSelWk *wkp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x004b8860
void DrawFileEmblem(struct FileSelWk *wkp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004b9330
void FUN_004b9330(struct task *param_1)
{
	if (!DAT_025d4cad)
	{
		return;
	}
	DrawMCharName(AvaGetlastPlayer(), 0xffffffff,
		*(float *)((char *)param_1 + 0x34) + 248.0 + 160.0, 122.0f,
		*(float *)((char *)param_1 + 0x0c) + -12.0, 0.7f, 0.7f);
}

// FUNCTION: SADX 0x004b9bc0
void FreeAdvaFileSelTask(void)
{
	if (DAT_05b42530)
	{
		DestroyTask(DAT_05b42530);
	}
}

// FUNCTION: SADX 0x004b9be0
void ChgSeqFileSel(void)
{
	((struct FileSelWk *)DAT_05b42530->awp)->NextMode = (enum AdvaModeEnum)7;
	((struct FileSelWk *)DAT_05b42530->awp)->PrevMode = (enum AdvaModeEnum)7;
}

// FUNCTION: SADX 0x004b9c10
void FUN_004b9c10(struct FileSelWk *param_1)
{
	ghSetPvrTexMaterial(-1);
	___njSetTexture(&texlist_ava_vmssel);
	DrawTitleBack(0.0f * ScreenRaitoX, ScreenRaitoX * 38.0f, param_1->BaseZ + -8.0f, ScreenRaitoX * 564.0f, ScreenRaitoY * 41.0f);
	ghDrawPvrTextureS(8, ScreenRaitoX * 42.0f, ScreenRaitoY * 46.0f, param_1->BaseZ + -14.0f, ScreenRaitoX, ScreenRaitoY);
	ghSetPvrTexMaterial(0x78004fff);
	DrawShadowWindow(ScreenRaitoX * 47.0f, ScreenRaitoY * 84.0f, param_1->BaseZ + -6.0f, ScreenRaitoX * 200.0f, ScreenRaitoX * 340.0f);
	AvaDrawInfo(param_1);
}

// FUNCTION: SADX 0x004ba980
void FUN_004ba980(void)
{
	if (DAT_05b42528 == 0)
	{
		DAT_05b42528 = _SOCMalloc(0x18, "..\\..\\src\\Advertise\\filesel.cpp", 3481);
		*(int *)((char *)DAT_05b42528 + 0x14) = 0;
	}
}

// STUB: SADX 0x004ba9c0
void FUN_004ba9c0(const char *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x004baaa0
void ReleaseLineList()
{
	struct _LIST_DATA *local_cg;
	struct _LIST_DATA *local_8g;

	if (!DAT_05b42528)
	{
		return;
	}
	while (*(struct _LIST_DATA **)((char *)DAT_05b42528 + 0x14))
	{
		local_cg = (struct _LIST_DATA *)DAT_05b42528;
		while (*(struct _LIST_DATA **)((char *)local_cg + 0x14))
		{
			local_8g = local_cg;
			local_cg = *(struct _LIST_DATA **)((char *)local_cg + 0x14);
		}
		_SOCFree(*(void **)((char *)local_cg + 0), "..\\..\\src\\Advertise\\filesel.cpp", 0xe4b);
		_SOCFree(local_cg, "..\\..\\src\\Advertise\\filesel.cpp", 0xe4c);
		*(struct _LIST_DATA **)((char *)local_8g + 0x14) = 0;
	}
	_SOCFree(DAT_05b42528, "..\\..\\src\\Advertise\\filesel.cpp", 0xe4f);
	DAT_05b42528 = 0;
}
