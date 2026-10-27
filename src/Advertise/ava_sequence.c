#include "decls.h"
void FUN_0059d6b0(struct task *param_1);
void FUN_0059d6b0(struct task *param_1);
void FUN_0059d6b0(struct task *param_1);
extern void (*DAT_02618a68[1])(void);
extern int DAT_05b3e350;
void FUN_0059da10(int param_1);
void FUN_0059d700(void *param_1);
void FUN_0059d6b0(struct task *param_1);

// STUB: SADX 0x0059d4b0
struct task *SetAdvaSequenceTask(struct SeqPrmType *prmp)
{
	struct task *local_8g;
	struct anywk *local_cg;

	if (DAT_05cda18c != 0)
	{
		while (1)
		{
		}
	}
	local_8g = CreateElementalTask(0, 3, sequence_exec);
	DAT_05cda18c = local_8g;
	if (DAT_05cda18c != 0)
	{
		local_cg = (struct anywk *)CAlloc(1, 0x24);
		local_8g->awp = local_cg;
		sequence_init(local_8g, prmp);
		local_8g->exec = sequence_exec;
		local_8g->dest = sequence_end;
	}
	return local_8g;
}

// FUNCTION: SADX 0x0059d650
void FUN_0059d650(struct task *param_1)
{
	struct task *local_8g;
	struct anywk *local_cg;
	local_8g = CreateElementalTask(0, 3, FUN_0059d6b0);
	if (local_8g != 0)
	{
		local_cg = (struct anywk *)CAlloc(1, 8);
		local_8g->awp = local_cg;
		local_cg->work.ptr[0] = param_1;
		local_cg->work.ul[1] = 1;
		local_8g->exec = FUN_0059d6b0;
	}
	return;
}

// STUB: SADX 0x0059d6b0
void FUN_0059d6b0(struct task *tp)
{
}

// STUB: SADX 0x0059d700
void FUN_0059d700(void *param_1)
{
}

// FUNCTION: SADX 0x0059d9d0
void sequence_end(struct task *tp)
{
	struct anywk *local_8;

	local_8 = tp->awp;
	DAT_05b3e350 = 0;
	AvaReleaseTexForAll();
	FUN_0059da10(*(int *)local_8);
	FreeDialogTask();
}

// FUNCTION: SADX 0x0059da10
void FUN_0059da10(int param_1)
{
	while (*(int *)param_1 != 0)
	{
		DAT_02618a68[*(int *)param_1]();
		param_1 += 0x10;
	}
}

// FUNCTION: SADX 0x0059da40
void FreeAdvaSequenceTask()
{
	if (DAT_05cda18c != 0)
	{
		DestroyTask(DAT_05cda18c);
		DAT_05cda18c = 0;
	}
}

// FUNCTION: SADX 0x0059da70
void FUN_0059da70(struct task *param_1)
{
	if (DAT_05cda18c->awp->work.ptr[1] != param_1)
	{
		DAT_05cda18c->awp->work.ptr[2] = DAT_05cda18c->awp->work.ptr[1];
		DAT_05cda18c->awp->work.ptr[1] = param_1;
	}
}

// FUNCTION: SADX 0x0059dab0
void CharSelAdvaModeProcedure(enum AdvaModeEnum nextnext)
{
	ChgCharSelNextAdvaMode(nextnext);
	CmnAdvaModeProcedure(ADVA_MODE_CHAR_SEL);
}

// FUNCTION: SADX 0x0059dad0
void CmnAdvaModeProcedure(enum AdvaModeEnum mode)
{
	struct anywk *local_8;
	local_8 = DAT_05cda18c->awp;
	EndAdvaBGM();
	*(char *)((char *)local_8 + 0x1e) = 1;
	*(int *)((char *)local_8 + 0x18) = (int)mode;
}
