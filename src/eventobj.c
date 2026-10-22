#include "decls.h"
struct facewk;
int FUN_005b3270(struct taskwk *param_1);
extern struct CCL_INFO DAT_0263d6f4;
extern int DAT_0263d6f0;

// FUNCTION: SADX 0x005b2450
void SetEventWork(struct taskwk *twp)
{
	struct eventwk *local_8;

	if (twp->ewp == 0)
	{
		local_8 = (struct eventwk *)CAlloc(1, 0x7c);
		twp->ewp = local_8;
		local_8->mode = 3;
	}
}

// STUB: SADX 0x005b24c0
void FreeEventAction(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005b2640
void DrawEventAction(struct taskwk *twp)
{
	DrawEventActionPL(twp, DAT_0263d6f0);
}

// STUB: SADX 0x005b2ab0
void EntryEventPath(struct taskwk *twp, struct EPATHTAG *path, float speed, int mode)
{
}

// FUNCTION: SADX 0x005b2b60
void FreeEventPath(struct taskwk *twp)
{
	struct EVENT_PATH_LIST *local_8;

	local_8 = twp->ewp->path.list;
	while (local_8 != 0)
	{
		struct EVENT_PATH_LIST *local_c;

		local_c = (struct EVENT_PATH_LIST *)*(void **)((char *)local_8 + 0xc);
		Free(local_8);
		local_8 = local_c;
	}
	twp->ewp->path.list = 0;
	twp->ewp->path.timer = 0.0f;
}

// STUB: SADX 0x005b3100
void SetEventFace(struct taskwk *twp, int no)
{
}

// STUB: SADX 0x005b3190
void ExecEventFace(struct taskwk *twp)
{
}

// STUB: SADX 0x005b3270
int FUN_005b3270(struct taskwk *twp)
{
	return (int)0;
}

// FUNCTION: SADX 0x005b3300
void ClrEventFace(struct taskwk *twp)
{
	struct facewk *local_8;

	local_8 = &twp->ewp->face;
	local_8->dataPtr = 0;
	local_8->tablePtr = 0;
	local_8->nbFrame = 0;
}

// FUNCTION: SADX 0x005b3340
struct task *CreateEventObject()
{
	struct task *local_8;

	local_8 = CreateElementalTask(2, 5, EventObject);
	SetEventWork(local_8->twp);
	CCL_Init(local_8, &DAT_0263d6f4, 1, 4);
	return local_8;
}
