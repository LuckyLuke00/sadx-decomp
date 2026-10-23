#include "decls.h"
static void DisplayTitleNew(float basez);
static void title_menu_exec(struct task *tp);

extern struct task *DAT_05b42a8c;
extern int DAT_05cd265c;

void FUN_005f22c0(struct task *param_1, struct ModeSelPrmType *param_2);
void FUN_004c0e10(void *param_1);
static void title_menu_disp(struct task *tp);

// FUNCTION: SADX 0x004c0680
struct task *SetAdvaTitleMenuTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05b42a8c = local_8g;
	if (DAT_05b42a8c != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = FUN_004c0db0;
	}
	return local_8g;
}

// STUB: SADX 0x004c06f0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x004c08b0
void FUN_004c08b0(void *param_1)
{
}

// FUNCTION: SADX 0x004c0db0
void FUN_004c0db0(struct task *param_1)
{
	char *local_8;

	local_8 = (char *)param_1->awp;
	if (*(int *)(local_8 + 0x18) == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)(local_8 + 0x18));
	title_menu_disp((struct task *)local_8);
	FUN_004c0e10(local_8);
	DAT_05cd265c = 1;
}

// FUNCTION: SADX 0x004c12c0
static void title_menu_disp(struct task *tp)
{
	DisplayTitleNew(*(float *)((char *)tp + 0x10));
}

// STUB: SADX 0x004c12e0
static void DisplayTitleNew(float basez)
{
}

// FUNCTION: SADX 0x004c1680
void FUN_004c1680(void)
{
	if (DAT_05b42a8c != 0)
	{
		DestroyTask(DAT_05b42a8c);
	}
}

// FUNCTION: SADX 0x004c16a0
void ChgSeqTitleMenu()
{
	*(int *)((char *)DAT_05b42a8c->awp + 4) = 0xe;
}
