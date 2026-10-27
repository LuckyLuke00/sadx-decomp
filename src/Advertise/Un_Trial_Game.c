#include "decls.h"
extern void *DAT_05edd898;
extern void *DAT_05edd8a0;
extern unsigned char DAT_0267b758;
extern void LoadTrialPicture();
extern void FUN_005f45f0(struct task *param_1);
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp);
extern void ghDefaultBlendingMode();
extern void ghSetPvrTexBaseColor(unsigned long color);
extern int DAT_05cd265c;
static void title_menu_disp(struct task *tp);
void FUN_005f3540(struct task *);
extern struct task *DAT_05edd89c;
void FUN_005f4610(float);

// FUNCTION: SADX 0x005f3480
struct task *SetAdvaTrialGameTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, FUN_005f3540);
	DAT_05edd89c = local_8g;
	if (DAT_05edd89c != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = FUN_005f3540;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005f3b60
static void title_menu_disp(struct task *tp)
{
	struct TitleMenuWk *local_8;

	local_8 = (struct TitleMenuWk *)tp->awp;
	if (local_8->BaseCol == 0 || DAT_0267b758 != 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	LoadTrialPicture();
	FUN_005f45f0((struct task *)local_8);
	DisplayTitleMenuCsr(local_8);
	DAT_05cd265c = 1;
}

#pragma optimize("", off)
// STUB: SADX 0x005f3bd0
static void DisplayTitleMenuCsr(struct TitleMenuWk *wkp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005f45f0
void FUN_005f45f0(struct task *param_1)
{
	FUN_005f4610(*(float *)((char *)param_1 + 0x10));
}

#pragma optimize("", off)
// STUB: SADX 0x005f4610
void FUN_005f4610(float param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x005f4690
void FreeAdvaTrialGameTask()
{
	void *local_8g;
	void *local_cj;
	void *local_14;
	void *local_10;

	if (DAT_05edd89c != 0)
	{
		DestroyTask(DAT_05edd89c);
	}
	if (DAT_05edd898 != 0)
	{
		FUN_0041c2d0(DAT_05edd898);
		local_cj = DAT_05edd898;
		local_8g = local_cj;
		local_8g ? (*(void *(__thiscall *)(void *, int))**(void ***)local_8g)(local_8g, 1) : 0;
		DAT_05edd898 = 0;
	}
	if (DAT_05edd8a0 != 0)
	{
		FUN_0041c2d0(DAT_05edd8a0);
		local_14 = DAT_05edd8a0;
		local_10 = local_14;
		local_10 ? (*(void *(__thiscall *)(void *, int))**(void ***)local_10)(local_10, 1) : 0;
		DAT_05edd8a0 = 0;
	}
}

// FUNCTION: SADX 0x005f4760
void FUN_005f4760(void)
{
	DAT_05edd89c->awp->work.ul[1] = 5;
}
