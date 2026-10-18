#include "decls.h"

extern struct task *DAT_05b42a8c;
extern int DAT_05cd265c;

void FUN_005f22c0(struct task *param_1, struct ModeSelPrmType *param_2);
void FUN_004c0e10(void *param_1);
void title_menu_disp(struct task *param_1);

// FUNCTION: SADX 0x004c0680
struct task *SetAdvaTitleMenuTask(struct ModeSelPrmType *param_1)
{
	void *data;
	struct task *ptr;

	ptr = CreateElementalTask(0, 4, title_menu_exec);
	DAT_05b42a8c = ptr;
	if (DAT_05b42a8c != 0)
	{
		data = CAlloc(1, 0x28);
		ptr->awp = (struct anywk *)data;
		FUN_005f22c0(ptr, param_1);
		ptr->exec = title_menu_exec;
		ptr->disp = FUN_004c0db0;
	}
	return ptr;
}

// FUNCTION: SADX 0x004c0db0
void FUN_004c0db0(struct task *param_1)
{
	char *work;

	work = (char *)param_1->awp;
	if (*(int *)(work + 0x18) == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)(work + 0x18));
	title_menu_disp((struct task *)work);
	FUN_004c0e10(work);
	DAT_05cd265c = 1;
}

// FUNCTION: SADX 0x004c12c0
void title_menu_disp(struct task *param_1)
{
	DisplayTitleNew(*(float *)((char *)param_1 + 0x10));
}
