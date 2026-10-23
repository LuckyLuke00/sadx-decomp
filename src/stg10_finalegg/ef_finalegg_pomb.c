#include "decls.h"

// FUNCTION: SADX 0x0088e470
void ef_finalegg_pomb_exec(struct sp_task *task_p, struct sp_link *link_p)
{
	long var1 = task_p->work[0].l;
	task_p->no = (short)task_p->frame;
	if (task_p->no >= (short)link_p->info->animnum)
	{
		task_p->no = (short)link_p->info->animnum - 1;
		SpFreeTask(task_p);
		return;
	}
	task_p->frame += *(float *)((char *)var1 + 8);
}

// STUB: SADX 0x0088e4c0
void CreateFinaleggPomb(struct NJS_POINT3 *pos, float scale)
{
}
