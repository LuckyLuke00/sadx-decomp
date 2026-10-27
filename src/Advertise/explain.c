#include "decls.h"
void FUN_006025c0(struct task *param_1);
void FUN_006025e0(int param_1);
void explain_exec(struct task *tp);
static void explain_disp(struct task *tp);
void ghDefaultBlendingMode();
void ghSetPvrTexBaseColor(unsigned long color);
void explain_disp(struct task *tp);
extern struct task *DAT_05cda18c;
void FUN_00602420(struct task *param_1);
extern struct task *DAT_05edd9b4;

// FUNCTION: SADX 0x00602360
struct task *SetAdvaExplainTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, FUN_00602430);
	DAT_05edd9b4 = local_8g;
	if (DAT_05edd9b4 != 0)
	{
		local_cg = CAlloc(1, 0x20);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_006023d0(local_8g, prmp);
		local_8g->exec = FUN_00602430;
		local_8g->disp = FUN_006026b0;
	}
	return local_8g;
}

// FUNCTION: SADX 0x006023d0
void FUN_006023d0(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8 = param_1->awp;

	local_8->work.ul[1] = *(unsigned long *)param_2;
	local_8->work.ul[2] = *(unsigned long *)((char *)param_2 + 4);
	local_8->work.f[3] = 5200.0f;
	local_8->work.ul[0] = 0;
	FUN_00602420((struct task *)local_8);
}

// FUNCTION: SADX 0x00602420
void FUN_00602420(struct task *param_1)
{
	param_1->dest = 0;
}

// FUNCTION: SADX 0x00602430
void FUN_00602430(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	if (*(int *)((char *)DAT_05cda18c->awp + 4) == 8 && *(int *)local_8 == 0)
	{
		FUN_006025c0((struct task *)local_8);
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)local_8 = 1;
	}
	if (*(int *)((char *)DAT_05cda18c->awp + 8) == 8 && *(int *)local_8 == 2)
	{
		FUN_006025e0((int)local_8);
		*(float *)((char *)local_8 + 0x10) = 0.0f;
		*(int *)local_8 = 3;
	}
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
		*(int *)((char *)DAT_05cda18c->awp + 0xc) = 8;
		explain_exec((struct task *)local_8);
		break;
	case 3:
		*(int *)((char *)local_8 + 0x14) = GetFadeOutColFromT(*(float *)((char *)local_8 + 0x10));
		*(float *)((char *)local_8 + 0x10) += 0.1f;
		if (*(float *)((char *)local_8 + 0x10) >= 1.0f)
		{
			AvaReleaseTexForEachMode((AdvaModeEnum)8);
			*(char *)((char *)DAT_05cda18c->awp + 0x1f) = 1;
			*(int *)local_8 = 0;
		}
		break;
	}
}

// FUNCTION: SADX 0x006025c0
void FUN_006025c0(struct task *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_EXPLAIN);
	FUN_00602420(param_1);
}

// FUNCTION: SADX 0x006025e0
void FUN_006025e0(int param_1)
{
	*(int *)((char *)DAT_05cda18c->awp + 0x10) = 0x65;
}

// STUB: SADX 0x00602600
void explain_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x006026b0
void FUN_006026b0(struct task *param_1)
{
	struct anywk *local_8 = param_1->awp;

	if (*(int *)((char *)local_8 + 0x14) == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)((char *)local_8 + 0x14));
	explain_disp((struct task *)local_8);
}

// FUNCTION: SADX 0x006026f0
static void explain_disp(struct task *tp)
{
	njPrintC(0xc0009, "GAME BUG");
}
