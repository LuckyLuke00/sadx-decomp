#include "decls.h"
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

// STUB: SADX 0x00602dd0
int FUN_00602dd0(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00602ff0
struct task *FUN_00602ff0(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, FUN_00603150);
	DAT_05edd9b8 = local_8g;
	if (DAT_05edd9b8)
	{
		local_cg = CAlloc(1, 0x54);
		local_8g->awp = (struct anywk *)local_cg;
		((void (*)(struct task *, struct ModeSelPrmType *))SetAdvaOptionSelTask)(local_8g, param_1);
		local_8g->exec = FUN_00603150;
		local_8g->disp = option_sel_disp;
	}
	return local_8g;
}

// STUB: SADX 0x00603060
struct task *SetAdvaOptionSelTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
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
