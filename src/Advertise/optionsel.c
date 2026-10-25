#include "decls.h"
void DrawOptionSelBg(struct _OptionSelWk *wkp);
struct _OptionSelWk;
void option_sel_disp(struct task *tp);
void FUN_006030c0(struct task *param_1);
extern struct task *DAT_05cda18c;
void FUN_00603150(struct task *param_1);

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
	ghDrawPvrTexture(local_9 + 0x2c, *(float *)(local_8g + 0) * ScreenRaitoX, *(float *)(local_8g + 4) * ScreenRaitoY, *(float *)((char *)wkp + 0xc) + -6.0, ScreenRaitoX, ScreenRaitoY);
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
	ghDrawPvrTexture(*(unsigned char *)((char *)wkp + 0x3f) + 0x24, *(float *)((char *)local_8 + 0x0) * ScreenRaitoX, *(float *)((char *)local_8 + 0x4) * ScreenRaitoY, *(float *)((char *)wkp + 0xc) + -6.0, ScreenRaitoX, ScreenRaitoY);
}

// STUB: SADX 0x00602e90
void DrawTvSetting(struct _OptionSelWk *wkp)
{
}

// STUB: SADX 0x00602f40
void DrawVibSetting(struct _OptionSelWk *wkp)
{
}

// STUB: SADX 0x00602ff0
struct task *FUN_00602ff0(struct ModeSelPrmType *param_1)
{
	return (struct task *)0;
}

// STUB: SADX 0x00603060
struct task *SetAdvaOptionSelTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// STUB: SADX 0x006030c0
void FUN_006030c0(struct task *param_1)
{
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
