#include "decls.h"
static void title_menu_disp(struct task *tp);
static void title_menu_exec(struct task *tp);
extern struct task *DAT_05edd77c;
void FUN_005e8f10(float);

// FUNCTION: SADX 0x005e8780
struct task *SetAdvaOpCreditsTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05edd77c = local_8g;
	if (DAT_05edd77c != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = title_menu_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// STUB: SADX 0x005e87f0
static void title_menu_exec(struct task *tp)
{
}

// STUB: SADX 0x005e89b0
void FUN_005e89b0(void *param_1)
{
}

// STUB: SADX 0x005e8d80
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005e8ef0
void FUN_005e8ef0(struct task *param_1)
{
	FUN_005e8f10(*(float *)((char *)param_1 + 0x10));
}

// STUB: SADX 0x005e9290
void FreeAdvaOpCreditsTask()
{
}
