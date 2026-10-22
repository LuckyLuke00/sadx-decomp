#include "decls.h"
void inetdemo_disp(struct task *tp);
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2);
extern struct task *DAT_05edd9a4;

// STUB: SADX 0x005fe0a0
struct task *SetAdvaInetDemoTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005fe110
void FUN_005fe110(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;
	local_8 = param_1->awp;
	*(int *)((char *)local_8 + 4) = *(int *)param_2;
	*(int *)((char *)local_8 + 8) = *(int *)((char *)param_2 + 4);
	*(float *)((char *)local_8 + 12) = 5400.0f;
	*(int *)local_8 = 0;
	*(int *)((char *)local_8 + 0x18) = 0;
}

// FUNCTION: SADX 0x005fe2f0
void FUN_005fe2f0(int param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_INETDEMO);
	*(int *)(param_1 + 0x18) = 0;
	SetAdvaBGM(0x37);
}

// STUB: SADX 0x005fe3f0
void inetdemo_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005ff890
void FreeAdvaInetDemoTask()
{
	if (DAT_05edd9a4)
	{
		DestroyTask(DAT_05edd9a4);
	}
}
