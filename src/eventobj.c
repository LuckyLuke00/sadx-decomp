#include "decls.h"
int FUN_005b3270(struct taskwk *param_1);
extern struct FACETBL *faceTbl[2];
extern "C" int rand(void);
int FUN_005b3270(struct taskwk *param_1);
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

// STUB: SADX 0x005b2540
void EntryEventAction(struct taskwk *twp, struct NJS_ACTION *ap, struct NJS_TEXLIST *lp, float speed, int mode, int linkframe)
{
}

// FUNCTION: SADX 0x005b2640
void DrawEventAction(struct taskwk *twp)
{
	DrawEventActionPL(twp, DAT_0263d6f0);
}

// FUNCTION: SADX 0x005b2ab0
void EntryEventPath(struct taskwk *twp, struct EPATHTAG *path, float speed, int mode)
{
	struct eventwk *local_ci;
	struct EVENT_PATH_LIST **local_8g;
	struct EVENT_PATH_LIST *local_10;

	local_ci = twp->ewp;
	local_8g = (struct EVENT_PATH_LIST **)&local_ci->path.list;
	if (*local_8g != 0)
	{
		do
		{
			local_8g = (struct EVENT_PATH_LIST **)((char *)*local_8g + 0xc);
		}
		while (*local_8g != 0);
	}
	else
	{
		if (mode & 2)
		{
			local_ci->path.pos = twp->pos;
		}
		else
		{
			local_ci->path.pos.z = 0.0f;
			local_ci->path.pos.y = 0.0f;
			local_ci->path.pos.x = 0.0f;
		}
	}
	local_10 = (struct EVENT_PATH_LIST *)CAlloc(1, 0x10);
	*local_8g = local_10;
	*(unsigned char *)((char *)local_10 + 0) = (unsigned char)mode;
	*(struct EPATHTAG **)((char *)local_10 + 4) = path;
	*(float *)((char *)local_10 + 8) = speed;
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

// STUB: SADX 0x005b2bc0
void ConvRotXYZ2YXZ(struct Angle3 *ang)
{
}

// FUNCTION: SADX 0x005b3100
void SetEventFace(struct taskwk *twp, int no)
{
	struct FACETBL *local_8g;
	struct FACETBL *local_cj;
	int local_10m;
	float local_14;

	if (no < 0)
	{
		ClrEventFace(twp);
	}
	else
	{
		local_cj = (struct FACETBL *)((char *)twp->ewp + 0x5c);
		local_8g = faceTbl[no];
		if (no == 0 || local_8g == 0 || local_8g->nbFrame == 0)
		{
			local_10m = rand();
			local_14 = (float)((double)local_10m / 32768.0);
			if (local_14 < 0.75)
			{
				local_8g = faceTbl[0];
			}
			else
			{
				local_8g = faceTbl[1];
			}
		}
		*(struct FACETBL **)((char *)local_cj + 0xc) = local_8g;
	}
}

// STUB: SADX 0x005b3190
void ExecEventFace(struct taskwk *twp)
{
}

// STUB: SADX 0x005b3270
int FUN_005b3270(struct taskwk *param_1)
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
