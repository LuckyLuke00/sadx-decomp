#include "decls.h"
extern int DAT_060b96b4;
extern struct task *DAT_060b9680[4];
extern const struct pastpc_data pastpc_data_tbl[1];

// FUNCTION: SADX 0x006bcbd0
void PASTPcEnd()
{
	while (DAT_060b96b4 != 0)
	{
		struct task *var1 = DAT_060b9680[DAT_060b96b4];
		DAT_060b96b4 = DAT_060b96b4 - 1;
		if (var1 != 0)
		{
			DestroyTask(var1);
			*(int *)((char *)DAT_060b9680 + 4 + DAT_060b96b4 * 4) = 0;
		}
	}
}

// STUB: SADX 0x006bcc90
void pastpc_chao_callback(struct obj *obj_p)
{
}

// FUNCTION: SADX 0x006bce20
void pastpc_end(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	struct pastpc_data *var2 = (struct pastpc_data *)&pastpc_data_tbl[var1->value.l];

	if (var2->index >= 0)
	{
		ReleasePlayersTexture(var2->index);
	}
	Free(*(void **)((char *)var1 + 0x30));
	InputHookDelete(task_p);
}

// STUB: SADX 0x006bce60
void __fastcall pastpc_exec_always(struct task *task_p)
{
}

// FUNCTION: SADX 0x006bcec0
void pastpc_talk(struct task *task_p)
{
	struct taskwk *var1;
	struct pastpc_data *var2;
	float var3;
	int var4;

	var1 = task_p->twp;
	if (var1->btimer == 0)
	{
		InputHookRelease();
		CancelLookingAtP(0);
		task_p->exec = pastpc_exec;
	}
	var1 = task_p->twp;
	var3 = var1->counter.f + 1.0f;
	var1->counter.f = var3;
	var2 = (struct pastpc_data *)&pastpc_data_tbl[var1->value.l];
	var4 = (int)var2->act_p->motion->nbFrame;
	var3 = (float)(unsigned int)var4;
	if (var3 - 1.0f < var1->counter.f)
	{
		var1->counter.f = 0.0f;
	}
	pastpc_draw(task_p);
}

// STUB: SADX 0x006bd080
void PASTPcInit()
{
}
