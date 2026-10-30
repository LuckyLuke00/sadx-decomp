#include "decls.h"
#include "advertise.h"
extern struct sp_task *DAT_05edbcc0;
extern int DAT_05edbc8c;
extern struct sp_task *DAT_05edbcb4;
extern unsigned long DAT_05edbcc4;
extern struct sp_link *DAT_05edbcb8;
extern int DAT_05edbcbc;
extern void FUN_005a63e0(struct sp_task *param_1, unsigned long param_2);
extern float DAT_05edbcc8;
extern struct NJS_SPRITE DAT_05edbc90;
extern int DAT_05edbcb0;

// FUNCTION: SADX 0x005a6390
void SpInitialize(struct sp_task *buffer, unsigned long size)
{
	DAT_05edbcb4 = buffer;
	DAT_05edbcc4 = size;
	FUN_005a63e0(DAT_05edbcb4, DAT_05edbcc4);
	DAT_05edbcb8 = 0;
	DAT_05edbcbc = 0;
	DAT_05edbcc8 = 0.0f;
}

// FUNCTION: SADX 0x005a63e0
void FUN_005a63e0(struct sp_task *param_1, unsigned long param_2)
{
	int local_8;

	DAT_05edbcc0 = param_1;
	DAT_05edbc8c = param_2;
	for (local_8 = 0; local_8 < (unsigned long)param_2 - 1; local_8++)
	{
		*(struct sp_task **)((char *)param_1 + local_8 * 0x50) = (struct sp_task *)((char *)param_1 + (local_8 + 1) * 0x50);
	}
	*(struct sp_task **)((char *)param_1 + (param_2 - 1) * 0x50) = 0;
}

// FUNCTION: SADX 0x005a6450
struct sp_task *SpCreateTask(struct sp_link *link, void (*exec)(struct sp_task *, struct sp_link *))
{
	struct sp_task *local_8;

	if (link == 0)
	{
		return 0;
	}
	if (DAT_05edbcc0 == 0)
	{
		return 0;
	}
	local_8 = DAT_05edbcc0;
	DAT_05edbcc0 = local_8->next;
	DAT_05edbc8c = DAT_05edbc8c - 1;
	local_8->next = link->head;
	link->head = local_8;
	link->numtask = link->numtask + 1;
	local_8->exec = exec;
	local_8->offset = DAT_05edbcc8;
	local_8->wrtZflg = 0;
	return local_8;
}

// FUNCTION: SADX 0x005a64e0
void SpFreeTask(struct sp_task *tp)
{
	tp->exec = 0;
}

// FUNCTION: SADX 0x005a64f0
struct sp_link *SpCreateLinkW(struct sp_info *info, unsigned long wksize)
{
	struct sp_link *local_8;

	if (info == 0)
	{
		return 0;
	}
	local_8 = (struct sp_link *)CAlloc(1, wksize + 0x1c);
	if (local_8 == 0)
	{
		return 0;
	}
	local_8->next = DAT_05edbcb8;
	DAT_05edbcb8 = local_8;
	DAT_05edbcbc = DAT_05edbcbc + 1;
	if (wksize > 0)
	{
		local_8->work = (void *)((char *)local_8 + 0x1c);
	}
	local_8->info = info;
	return local_8;
}

// FUNCTION: SADX 0x005a6560
void SpFreeLink(struct sp_link *link)
{
	if ((link->sysflag & 2) != 0)
	{
		return;
	}
	link->sysflag |= 2;
}

// STUB: SADX 0x005a6590
void SpLoop()
{
}

// FUNCTION: SADX 0x005a67c0
void SpLoopOnlyDisplay()
{
	int local_8g = 0;
	struct NJS_SPRITE *local_cg;
	struct sp_link *local_10g;

	___njFogDisable();
	((SOCRender*)DAT_05ab39ac)->FUN_004199b0(false);
	local_10g = DAT_05edbcb8;
	while (local_10g != 0)
	{
		struct sp_info *local_14g = local_10g->info;
		struct sp_task *local_18g = local_10g->head;
		local_cg = &DAT_05edbc90;
		local_cg->tlist = local_14g->texlist;
		local_cg->tanim = local_14g->texanim;
		___njColorBlendingMode(0, local_14g->srcblend);
		___njColorBlendingMode(1, local_14g->dstblend);
		while (local_18g != 0)
		{
			if (local_18g->exec != 0)
			{
				float local_1cg;
				___njSetConstantMaterial(&local_18g->argb);
				local_cg->p = local_18g->pos;
				local_cg->sy = local_18g->scl;
				local_cg->sx = local_cg->sy;
				local_cg->ang = local_18g->ang;
				local_1cg = local_18g->offset;
				DAT_05b3df40 = local_1cg;
				late_DrawSprite3D(local_cg, local_18g->no, 0x33, local_18g->wrtZflg | 4);
				DAT_05b3df40 = 0.0f;
				local_8g = local_8g + 1;
			}
			local_18g = local_18g->next;
		}
		local_10g = local_10g->next;
	}
	ResetMaterial();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	___njFogEnable();
	DAT_05edbcb0 = local_8g;
}

// FUNCTION: SADX 0x005a6940
void SpDestroyAll()
{
	int local_cg;
	int local_8g;

	FUN_005a63e0(DAT_05edbcb4, DAT_05edbcc4);
	local_cg = (int)DAT_05edbcb8;
	while (local_cg != 0)
	{
		local_8g = *(int *)local_cg;
		Free((void *)local_cg);
		local_cg = local_8g;
	}
	DAT_05edbcb8 = 0;
	DAT_05edbcbc = 0;
}

// STUB: SADX 0x005a69a0
void SpDestroyTaskAll()
{
}

// FUNCTION: SADX 0x005a6a30
void SpSetZOffset(float offset)
{
	DAT_05edbcc8 = offset;
}
