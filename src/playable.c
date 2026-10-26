#include "decls.h"
void FUN_005b5aa0(...);
void CPlayable_Dest(struct task *tp);
void CPlayable_Exec(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern struct task *DAT_05edbe70;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern struct CPlayableInfo gPlayableInfo[1];
extern long DAT_05edbe78;

// FUNCTION: SADX 0x005b5ab0
int Playable(long playerno)
{
	struct CPlayableInfo *local_8;

	local_8 = &gPlayableInfo[0];
	while (local_8->playerno >= 0 && local_8->playerno != playerno)
	{
		local_8 = local_8 + 1;
	}
	if (local_8->playerno < 0)
	{
		return 0;
	}
	if (SeqCheckPlayable(playerno))
	{
		return 0;
	}
	SeqPlayable(playerno);
	FUN_005b5b20(local_8);
	return 1;
}

// FUNCTION: SADX 0x005b5b20
struct task *FUN_005b5b20(void *param_1)
{
	struct task *local_8g;
	struct taskwk *local_cg;

	local_8g = CreateElementalTask(2, 5, CPlayable_Exec);
	if (local_8g != NULL)
	{
		local_8g->exec = CPlayable_Exec;
		local_8g->disp = (void (*)(struct task *))FUN_005b5aa0;
		local_8g->dest = CPlayable_Dest;
		local_cg = local_8g->twp;
		local_cg->value.l = (long)param_1;
		local_cg->counter.l = 0x14;
		local_cg->mode = 0;
		DAT_05edbe78 = 1;
	}
	memset(&DAT_05edbe70, 0, 8);
	return local_8g;
}

// FUNCTION: SADX 0x005b5bb0
void CPlayable_Dest(struct task *tp)
{
	SeqSave();
	DAT_05edbe78 = 0;
}

// FUNCTION: SADX 0x005b5de0
int PlayableWait()
{
	return DAT_05edbe78;
}
