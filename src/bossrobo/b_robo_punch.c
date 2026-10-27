#include "decls.h"
extern struct CCL_INFO colliInfoPunch[1];
extern int DAT_060bcea0;
void punchColliSet();
void RoboPunch_Init();
extern int DAT_060bceb0;
extern int DAT_060bceb4;
extern int DAT_05b9d838;
extern int DAT_060bcea4;
extern int DAT_060bcea8;

// FUNCTION: SADX 0x006de450
void dest_colli(struct task *pTask)
{
	DAT_060bcea4 = 0;
	DAT_060bcea8 = 0;
}

// FUNCTION: SADX 0x006de460
void exec_colli(struct task *pTask)
{
	if (DAT_05b9d838 == 0 && DAT_060bcea8 != 0)
	{
		EntryColliList(pTask->twp);
	}
}

// STUB: SADX 0x006de490
void disp_ChainElec(struct task *pTask)
{
}

// FUNCTION: SADX 0x006de6d0
void dest_ChainElec(struct task *pTask)
{
	DAT_060bceb4 = 0;
	DAT_060bceb0 = 0;
}

// FUNCTION: SADX 0x006df100
void punchColliSet()
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 4, exec_colli);
	if (var1 != NULL)
	{
		var2 = var1->twp;
		var2->pos.x = 0.0f;
		var2->pos.y = 752.09f;
		var2->pos.z = -385.89f;
		CCL_Init(var1, (struct CCL_INFO *)&colliInfoPunch, 0x20, 4);
		SET_COLLI_RANGE(var1->twp->cwp, 1000.0f);
		var1->dest = dest_colli;
	}
	DAT_060bcea4 = (int)var1;
}

#pragma optimize("", off)
// STUB: SADX 0x006df170
void RoboPunch_Init()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006df1f0
void FUN_006df1f0()
{
	DAT_060bcea0 = 0;
	punchColliSet();
	RoboPunch_Init();
}
