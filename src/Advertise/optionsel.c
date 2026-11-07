#include "decls.h"
void FUN_006032f0(struct task *param_1);
void FUN_00603340(struct anywk *param_1);
void option_sel_sub_exec(struct _OptionSelWk *wkp);
extern int DAT_0099b0a8;
extern struct NJS_TEXLIST texlist_ava_option;
extern float ScreenRaitoX;
extern float ScreenRaitoY;
void ghSetPvrTexMaterial(unsigned long color);
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void ghDrawPvrTextureS(int index, float x, float y, float z, float sx, float sy);
void FUN_00603150(struct task *param_1);
extern struct task *DAT_05edd9b8;
void DrawOptionSelBg(struct _OptionSelWk *wkp);
struct _OptionSelWk;
void option_sel_disp(struct task *tp);
void FUN_006030c0(struct task *param_1);
extern struct task *DAT_05cda18c;

// STUB: SADX 0x00602730
signed char LangToDlgNum(signed char csr)
{
	return (signed char)0;
}

// STUB: SADX 0x00602790
void DrawOptionSelDlgSub2(struct DDlgType *dlgp)
{
}

// STUB: SADX 0x006028a0
void DrawOptionSelDlgSub1(struct DDlgType *dlgp)
{
}

// STUB: SADX 0x006029b0
void DrawIconSndTest(struct _OptionSelWk *wkp)
{
}

// STUB: SADX 0x00602b40
void DrawIconMesSetUp(struct _OptionSelWk *wkp)
{
}

// FUNCTION: SADX 0x00602d10
void DrawIconFileSel(struct _OptionSelWk *wkp)
{
	int local_8g;
	unsigned char local_9;

	local_8g = *(int *)((char *)wkp + 0x48) + 0x60;
	ghSetPvrTexMaterial(0xffffffff);
	___njSetTexture(&texlist_ava_option);
	switch (*(char *)((char *)wkp + 0x44))
	{
		case 0:
			local_9 = 0;
			break;
		case 1:
			local_9 = 1;
			break;
		default:
			local_9 = 2;
			break;
	}
	ghDrawPvrTextureS(local_9 + 0x2c, *(float *)local_8g * ScreenRaitoX, *(float *)(local_8g + 4) * ScreenRaitoY, *(float *)((char *)wkp + 0xc) + -6.0, ScreenRaitoX, ScreenRaitoY);
}

// STUB: SADX 0x00602dd0
int FUN_00602dd0(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00602df0
void DrawLangSel(struct _OptionSelWk *wkp)
{
	void *local_8;

	local_8 = (void *)((char *)(*(void **)((char *)wkp + 0x48)) + 0xc0);
	ghSetPvrTexMaterial(0xffffffff);
	___njSetTexture(&texlist_ava_option);
	ghDrawPvrTextureS(*(unsigned char *)((char *)wkp + 0x3f) + 0x24, *(float *)((char *)local_8 + 0x0) * ScreenRaitoX, *(float *)((char *)local_8 + 0x4) * ScreenRaitoY, *(float *)((char *)wkp + 0xc) + -6.0, ScreenRaitoX, ScreenRaitoY);
}

// FUNCTION: SADX 0x00602e90
void DrawTvSetting(struct _OptionSelWk *wkp)
{
	int local_8g;
	unsigned char local_9;

	local_8g = *(int *)((char *)wkp + 0x48) + 0x120;
	local_9 = *(unsigned char *)((char *)wkp + 0x3e);
	if (local_9 == 3)
		local_9 = 1;
	if (local_9 > 3)
		local_9 = 0;
	ghDrawPvrTextureS(local_9 + 0x20, *(float *)local_8g * ScreenRaitoX, *(float *)(local_8g + 4) * ScreenRaitoY, *(float *)((char *)wkp + 0xc) + -6.0, ScreenRaitoX, ScreenRaitoY);
}

// FUNCTION: SADX 0x00602f40
void DrawVibSetting(struct _OptionSelWk *wkp)
{
	int local_8g;
	unsigned char local_9;

	local_8g = *(int *)((char *)wkp + 0x48) + 0xf0;
	switch (*(char *)((char *)wkp + 0x42))
	{
		case 8:
			local_9 = 0;
			break;
		case 10:
			local_9 = 2;
			break;
		default:
			local_9 = 1;
			break;
	}
	ghDrawPvrTextureS(local_9 + 0x29, *(float *)local_8g * ScreenRaitoX, *(float *)(local_8g + 4) * ScreenRaitoY, *(float *)((char *)wkp + 0xc) + -6.0, ScreenRaitoX, ScreenRaitoY);
}

// FUNCTION: SADX 0x00602ff0
struct task *SetAdvaOptionSelTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, FUN_00603150);
	DAT_05edd9b8 = local_8g;
	if (DAT_05edd9b8 != 0)
	{
		local_cg = CAlloc(1, 0x54);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_00603060(local_8g, prmp);
		local_8g->exec = FUN_00603150;
		local_8g->disp = option_sel_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x00603060
void FUN_00603060(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct FileSelWk *local_8;

	local_8 = (struct FileSelWk *)param_1->awp;
	local_8->PrevMode = *(enum AdvaModeEnum *)param_2;
	local_8->NextMode = *(enum AdvaModeEnum *)((char *)param_2 + 4);
	local_8->BaseZ = 5500.0f;
	local_8->Stat = ADVA_STAT_REQWAIT;
	local_8->CsrCol = 0;
	FUN_006030c0((struct task *)local_8);
}

// FUNCTION: SADX 0x006030c0
void FUN_006030c0(struct task *param_1)
{
	param_1->dest = 0;
	*(int *)((char *)param_1 + 0x38) = 0;
	*(float *)((char *)param_1 + 0x34) = 1.0f;
	*(char *)((char *)param_1 + 0x3c) = 0xff;
	*(int *)((char *)param_1 + 0x24) = 0;
	*(char *)((char *)param_1 + 0x28) = 0;
	*(char *)((char *)param_1 + 0x29) = 0;
	*(char *)((char *)param_1 + 0x3e) = 0;
	*(char *)((char *)param_1 + 0x3f) = 0;
	*(char *)((char *)param_1 + 0x2a) = 0;
	*(char *)((char *)param_1 + 0x2b) = 0;
	*(char *)((char *)param_1 + 0x2c) = 0;
	*(char *)((char *)param_1 + 0x2d) = 0;
	*(char *)((char *)param_1 + 0x43) = 0;
	*(char *)((char *)param_1 + 0x42) = 0;
	*(int *)((char *)param_1 + 0x48) = (int)&DAT_0099b0a8;
	*(int *)((char *)param_1 + 0x4c) = 6;
}

// FUNCTION: SADX 0x00603150
void FUN_00603150(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	if (DAT_05cda18c->awp->work.sl[1] == 7 && *(int *)local_8 == 0)
	{
		FUN_006032f0((struct task *)local_8);
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)local_8 = 1;
	}
	if (DAT_05cda18c->awp->work.sl[2] == 7 && *(int *)local_8 == 2)
	{
		FUN_005b5aa0(local_8);
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)local_8 = 3;
	}
	FUN_00603340(local_8);
	switch (*(int *)local_8)
	{
	case 0:
		*(int *)((char *)local_8 + 0x14) = 0;
		break;
	case 1:
		*(int *)((char *)local_8 + 0x14) = GetFadeInColFromT(*(float *)((char *)local_8 + 0x10));
		*(float *)((char *)local_8 + 0x10) += 0.1f;
		if (*(float *)((char *)local_8 + 0x10) >= 1.0f)
		{
			*(int *)local_8 = 2;
		}
		break;
	case 2:
		*(int *)((char *)local_8 + 0x14) = 0xffffffff;
		DAT_05cda18c->awp->work.sl[3] = 7;
		option_sel_sub_exec((struct _OptionSelWk *)local_8);
		break;
	case 3:
		*(int *)((char *)local_8 + 0x14) = GetFadeOutColFromT(*(float *)((char *)local_8 + 0x10));
		*(float *)((char *)local_8 + 0x10) += 0.1f;
		if (*(float *)((char *)local_8 + 0x10) >= 1.0f)
		{
			AvaReleaseTexForEachMode((AdvaModeEnum)7);
			*(char *)((char *)DAT_05cda18c->awp + 0x1f) = 1;
			*(int *)local_8 = 0;
		}
		break;
	}
}

// FUNCTION: SADX 0x006032f0
void FUN_006032f0(struct task *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_OPTION_SEL);
	SetAdvaModeBGM((enum AvaBgmEnum)2);
	SetAdvaSerifu((enum AvaSerifuModeEnum)5);
	FUN_006030c0(param_1);
	if (DAT_05cda18c->awp->work.ul[2] == 6)
	{
		param_1->ocp = NULL;
	}
}

// STUB: SADX 0x006041f0
void ChangeLanguageMode(struct _OptionSelWk *wkp)
{
}

// FUNCTION: SADX 0x006042d0
void option_sel_disp(struct task *tp)
{
	struct _OptionSelWk *local_8;

	local_8 = (struct _OptionSelWk *)tp->awp;
	if (*(int *)((char *)local_8 + 0x14) == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)((char *)local_8 + 0x14));
	DrawSkyBg(*(float *)((char *)local_8 + 0xc) + -4.0);
	DrawOptionSelBg(local_8);
	DispOptionSelCsr(local_8);
}

// STUB: SADX 0x00604340
void DispOptionSelCsr(struct _OptionSelWk *wkp)
{
}

// STUB: SADX 0x00604500
void DrawOptionSelBg(struct _OptionSelWk *wkp)
{
}
