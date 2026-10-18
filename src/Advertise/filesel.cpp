#include "decls.h"

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
void DrawFileDelDlgSub(struct DDlgType *param_1)
{
	int w;
	int h;
	float x;
	float y;
	struct FileSelWk *wk;

	wk = (struct FileSelWk *)DAT_05b42530->awp;
	___njSetTexture(&texlist_ava_fsdlg);
	ghSetPvrTexMaterial(-1);
	ghGetPvrTextureSize(&texlist_ava_fsdlg, 3, &w, &h);
	x = w * 0.5 + -113.0;
	y = h * 0.5 + -43.0;
	((void (*)(int, float, float, float, float, float))ghDrawPvrTexture)(0x4000003, (float)(x * param_1->SclX + param_1->CntrX) * ScreenRaitoX, (float)(y * param_1->SclY + param_1->CntrY) * ScreenRaitoY, param_1->BaseZ + -6.0, param_1->SclX * ScreenRaitoX, param_1->SclY * ScreenRaitoY);
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
	void *pWk;
	struct task *pTask;

	pTask = CreateElementalTask(0, 3, file_sel_exec);
	DAT_05b42530 = pTask;
	if (DAT_05b42530)
	{
		pWk = CAlloc(1, 0x38);
		pTask->awp = (struct anywk *)pWk;
		((void (*)(struct task *, struct ModeSelPrmType *))SetAdvaFileSelTask)(pTask, param_1);
		pTask->exec = file_sel_exec;
		pTask->disp = FUN_004b83c0;
	}
	return pTask;
}

// FUNCTION: SADX 0x004b6d40
struct task *SetAdvaFileSelTask(struct ModeSelPrmType *param_1)
{
	struct FileSelWk *wk;

	wk = (struct FileSelWk *)((struct task *)param_1)->awp;
	wk->PrevMode = *(enum AdvaModeEnum *)*(&param_1 + 1);
	wk->NextMode = *(enum AdvaModeEnum *)((char *)*(&param_1 + 1) + 4);
	wk->BaseZ = 5900.0f;
	wk->Stat = ADVA_STAT_REQWAIT;
	FUN_004b6c50(wk);
}

// FUNCTION: SADX 0x004b6d90
void file_sel_exec(struct task *param_1)
{
	struct FileSelWk *wk;

	wk = (struct FileSelWk *)param_1->awp;
	if (*(int *)((char *)DAT_05cda18c->awp + 4) == 2 && wk->Stat == ADVA_STAT_REQWAIT)
	{
		FileSelModeWakeProcedure(wk);
		wk->T = 0.0f;
		wk->Stat = ADVA_STAT_FADEIN;
	}
	if (*(int *)((char *)DAT_05cda18c->awp + 8) == 2 && wk->Stat == ADVA_STAT_KEEP)
	{
		FUN_004b7800(wk);
		wk->T = 0.0f;
		wk->Stat = ADVA_STAT_FADEOUT;
	}
	switch (wk->Stat)
	{
	case ADVA_STAT_REQWAIT:
		wk->BaseCol = 0;
		break;
	case ADVA_STAT_FADEIN:
		wk->BaseCol = GetFadeInColFromT(wk->T);
		wk->T = (float)(*(volatile int *)&DAT_05b9d848 * 0.05) + wk->T;
		if (wk->T >= 1.0)
		{
			CloseDialog();
			wk->Stat = ADVA_STAT_KEEP;
		}
		DAT_05cd2604 = 1;
		break;
	case ADVA_STAT_KEEP:
		wk->BaseCol = -1;
		*(int *)((char *)DAT_05cda18c->awp + 0xc) = 2;
		file_sel_sub_exec(wk);
		break;
	case ADVA_STAT_FADEOUT:
		wk->BaseCol = GetFadeOutColFromT(wk->T);
		wk->T = (float)(*(volatile int *)&DAT_05b9d848 * 0.05) + wk->T;
		if (wk->T > 1.0)
		{
			wk->T = 1.0f;
		}
		if (wk->T >= 1.0)
		{
			AvaReleaseTexForEachMode(ADVA_MODE_FILE_SEL);
			ghReleaseFontTexture(Ascii16x16FontInfo);
			*((unsigned char *)DAT_05cda18c->awp + 0x1f) = 1;
			wk->Stat = ADVA_STAT_REQWAIT;
			ReleaseLineList();
		}
		break;
	}
}

// FUNCTION: SADX 0x004b7800
void FUN_004b7800(struct FileSelWk *param_1)
{
	void *a;
	void *b;
	void *c;
	void *d;

	if (DAT_05b3e378)
	{
		FUN_0041c2d0(DAT_05b3e378);
		b = DAT_05b3e378;
		a = b;
		a ? (*(void *(__thiscall *)(void *, int))**(void ***)a)(a, 1) : 0;
		DAT_05b3e378 = 0;
	}
	if (DAT_05b3e37c)
	{
		FUN_0041c2d0(DAT_05b3e37c);
		c = DAT_05b3e37c;
		d = c;
		d ? (*(void *(__thiscall *)(void *, int))**(void ***)d)(d, 1) : 0;
		DAT_05b3e37c = 0;
	}
}

// FUNCTION: SADX 0x004b83c0
void FUN_004b83c0(struct task *param_1)
{
	struct FileSelWk *wk;

	wk = (struct FileSelWk *)param_1->awp;
	if (wk->BaseCol == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	wk->OfsX = 20.0f;
	DrawSkyBg(wk->BaseZ + -2.0);
	FUN_004b9c10(wk);
	ghSetPvrTexBaseColor(wk->BaseCol);
	DrawFileSelScoreWindow(wk);
	DrawFileSelBallChar(wk);
	DrawFileSelCsr(wk);
	DrawFileSelBg(wk);
	DrawFileEmblem(wk);
	file_sel_disp((struct task *)wk);
	DrawStartChiten(wk);
	DrawSaishuuClear(wk);
	DrawPlayTime(wk);
	if (DAT_05b4252c)
	{
		AlertWindowTask(DAT_05b42524);
	}
	if (DAT_05b3e356)
	{
		AlertWindowTask(DAT_05b42520);
	}
}
