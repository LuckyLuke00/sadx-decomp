#include "decls.h"
extern struct obj object_kanban_eggkanban_eggkanban[];
void eggkanban_draw(struct task *task_p);

// FUNCTION: SADX 0x00894080
void eggkanban_draw(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	SaveControl3D();
	OffControl3D(0x220);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip(object_kanban_eggkanban_eggkanban[0].model, 1.0f);
	if (var1->value.ptr)
	{
		late_DrawModelClip((struct NJS_MODEL *)var1->value.ptr, 0, 1.0f);
	}
	else
	{
		late_DrawModelClip(object_kanban_eggkanban_eggkanban[0].sibling->model, 0, 1.0f);
	}
	late_DrawModelClip(object_kanban_eggkanban_eggkanban[0].child->model, 1, 1.0f);
	njPopMatrix(1);
	LoadControl3D();
}

// FUNCTION: SADX 0x00894140
void eggkanban_end(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (var1->value.ptr != 0)
	{
		Free(*(void **)((char *)var1->value.ptr + 0x10));
		Free(var1->value.ptr);
	}
}

// STUB: SADX 0x008941e0
void eggkanban_exec(struct task *task_p)
{
}
