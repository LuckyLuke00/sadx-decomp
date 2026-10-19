#include "decls.h"
extern void *DAT_05b42528;
void *_SOCMalloc(unsigned int size, const char *file, int line);

#pragma warning(disable: 4716)

void _SOCFree(void *p, const char *file, int line);
void FUN_004b6c50(struct FileSelWk *param_1);
void FUN_004b7800(struct FileSelWk *param_1);
void FUN_004b83c0(struct task *param_1);
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
extern void *DAT_05b3e378;
extern void *DAT_05b3e37c;

// FUNCTION: SADX 0x004b6b50
void DrawFileDelDlgSub(struct DDlgType *dlgp)
{
	int local_8g;
	int local_cj;
	float local_14h;
	float local_10m;
	struct FileSelWk *local_18;

	local_18 = (struct FileSelWk *)DAT_05b42530->awp;
	___njSetTexture(&texlist_ava_fsdlg);
	ghSetPvrTexMaterial(-1);
	ghGetPvrTextureSize(&texlist_ava_fsdlg, 3, &local_8g, &local_cj);
	local_14h = local_8g * 0.5 + -113.0;
	local_10m = local_cj * 0.5 + -43.0;
	((void (*)(int, float, float, float, float, float))ghDrawPvrTexture)(0x4000003, (float)(local_14h * dlgp->SclX + dlgp->CntrX) * ScreenRaitoX, (float)(local_10m * dlgp->SclY + dlgp->CntrY) * ScreenRaitoY, dlgp->BaseZ + -6.0, dlgp->SclX * ScreenRaitoX, dlgp->SclY * ScreenRaitoY);
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
struct task *FUN_004b6cd0(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, file_sel_exec);
	DAT_05b42530 = local_8g;
	if (DAT_05b42530)
	{
		local_cg = CAlloc(1, 0x38);
		local_8g->awp = (struct anywk *)local_cg;
		((void (*)(struct task *, struct ModeSelPrmType *))SetAdvaFileSelTask)(local_8g, param_1);
		local_8g->exec = file_sel_exec;
		local_8g->disp = FUN_004b83c0;
	}
	return local_8g;
}

// FUNCTION: SADX 0x004b6d40
struct task *SetAdvaFileSelTask(struct ModeSelPrmType *prmp)
{
	struct FileSelWk *local_8;

	local_8 = (struct FileSelWk *)((struct task *)prmp)->awp;
	local_8->PrevMode = *(enum AdvaModeEnum *)*(&prmp + 1);
	local_8->NextMode = *(enum AdvaModeEnum *)((char *)*(&prmp + 1) + 4);
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
		local_8->T = (float)(*(volatile int *)&DAT_05b9d848 * 0.05) + local_8->T;
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
		local_8->T = (float)(*(volatile int *)&DAT_05b9d848 * 0.05) + local_8->T;
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
	void *local_8g;
	void *local_cj;
	void *local_14;
	void *local_10;

	if (DAT_05b3e378)
	{
		FUN_0041c2d0(DAT_05b3e378);
		local_cj = DAT_05b3e378;
		local_8g = local_cj;
		local_8g ? (*(void *(__thiscall *)(void *, int))**(void ***)local_8g)(local_8g, 1) : 0;
		DAT_05b3e378 = 0;
	}
	if (DAT_05b3e37c)
	{
		FUN_0041c2d0(DAT_05b3e37c);
		local_14 = DAT_05b3e37c;
		local_10 = local_14;
		local_10 ? (*(void *(__thiscall *)(void *, int))**(void ***)local_10)(local_10, 1) : 0;
		DAT_05b3e37c = 0;
	}
}

// FUNCTION: SADX 0x004b83c0
void FUN_004b83c0(struct task *param_1)
{
	struct FileSelWk *local_8;

	local_8 = (struct FileSelWk *)param_1->awp;
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
	file_sel_disp((struct task *)local_8);
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

// FUNCTION: SADX 0x004ba980
void FUN_004ba980(void)
{
	if (DAT_05b42528 == 0)
	{
		DAT_05b42528 = _SOCMalloc(0x18, "..\\..\\src\\Advertise\\filesel.cpp", 3481);
		*(int *)((char *)DAT_05b42528 + 0x14) = 0;
	}
}
