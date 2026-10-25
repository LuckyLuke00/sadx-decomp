#include "decls.h"
void DisplayFinTitle(struct TitleNewWk *wkp, float basez);
void DrawDXTitle(struct TitleNewWk *wkp);
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2);
void FUN_005a0070(struct task *param_1);
void FUN_005a0070(struct task *param_1);
extern struct task *DAT_05cda19c;

// FUNCTION: SADX 0x0059f950
struct task *SetAdvaTitleNewTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(8, 3, title_new_exec);
	DAT_05cda19c = local_8g;
	if (DAT_05cda19c)
	{
		local_cg = CAlloc(1, 0x48);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005fe110(local_8g, prmp);
		local_8g->exec = title_new_exec;
		local_8g->disp = FUN_005a0070;
	}
	return local_8g;
}

// FUNCTION: SADX 0x0059fd80
void FUN_0059fd80(struct task *param_1)
{
	if (param_1->awp)
	{
		DestroyTask((struct task *)param_1->awp);
		param_1->awp = NULL;
	}
}

// FUNCTION: SADX 0x005a0070
void FUN_005a0070(struct task *param_1)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	if (*(int *)((char *)local_8 + 0x14) == 0)
	{
		return;
	}
	if (*(int *)((char *)local_8 + 0x18) < 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)((char *)local_8 + 0x14));
	FUN_007d21b0((void *)3);
	title_new_disp((struct task *)local_8);
}

// FUNCTION: SADX 0x005a00d0
void title_new_disp(struct task *tp)
{
	if (!FUN_0040ae00())
	{
		DisplayFinTitle((struct TitleNewWk *)tp, ((struct TitleNewWk *)tp)->BaseZ);
	}
	DrawDXTitle((struct TitleNewWk *)tp);
}

// FUNCTION: SADX 0x005a06b0
void FreeAdvaTitleNewTask()
{
	if (DAT_05cda19c)
	{
		DestroyTask(DAT_05cda19c);
	}
}

// FUNCTION: SADX 0x005a06d0
void ChgSeqTitleNew()
{
	DAT_05cda19c->awp->work.ul[2] = 0xe;
}
