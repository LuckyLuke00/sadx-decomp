#include "decls.h"
void FUN_006025c0(struct task *param_1);
void FUN_006025e0();
void explain_exec(struct task *tp);
static void explain_disp(struct task *tp);
void ghDefaultBlendingMode();
void ghSetPvrTexBaseColor(unsigned long color);
void explain_disp(struct task *tp);
extern struct task *DAT_05cda18c;
void FUN_00602420(struct task *param_1);

// STUB: SADX 0x006023d0
void SetAdvaExplainTask(struct task *param_1, struct ModeSelPrmType *param_2)
{
}

// FUNCTION: SADX 0x00602420
void FUN_00602420(struct task *param_1)
{
	param_1->dest = 0;
}

// STUB: SADX 0x00602430
void FUN_00602430(struct task *param_1)
{
}

// FUNCTION: SADX 0x006025c0
void FUN_006025c0(struct task *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_EXPLAIN);
	FUN_00602420(param_1);
}

// FUNCTION: SADX 0x006025e0
void FUN_006025e0()
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
