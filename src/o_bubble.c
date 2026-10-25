#include "decls.h"
void FUN_008d94c0(struct taskwk *param_1, int param_2);
void FUN_008d94c0(struct taskwk *param_1, int param_2);
extern void ___njSetConstantMaterial(struct NJS_ARGB *);
extern void ___njColorBlendingMode(int, int);
extern void ResetMaterial();
void bbl_ripple_set(struct NJS_POINT3 *pos_p, float speed, float fade, float size);
void FUN_008d9e40(struct task *param_1);
extern void bubble_child_exec_appear(struct task *task_p);
extern void bubble_child_draw(struct task *task_p);
void FUN_008d94c0(struct taskwk *param_1, int param_2);
extern struct NJS_SPRITE sprite_o_bubble;
extern int DAT_05b9d838;
void FUN_008d97e0(struct taskwk *param_1);
void FUN_008d9000(struct taskwk *param_1, float param_2);

// STUB: SADX 0x008d8930
void ObjectBubble(struct task *task_p)
{
}

// STUB: SADX 0x008d8a20
void ObjectBubbleSmall(struct task *bbls_task_p)
{
}

// STUB: SADX 0x008d8b00
void bubble_exec(struct task *task_p)
{
}

// STUB: SADX 0x008d8c40
void bubble_child_init(struct task *task_p)
{
}

// FUNCTION: SADX 0x008d8d30
void bubble_child_exec_appear(struct task *task_p)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;
	local_cg = task_p->ptp->twp;
	local_8g = task_p->twp;
	local_8g->scl.x = local_8g->scl.x + local_8g->timer.f;
	FUN_008d9000(local_8g, local_8g->scl.x);
	bubble_child_exec(task_p);
	if (*(float *)((char *)local_cg + 0x24) + 10.0f < *(float *)((char *)local_8g + 0x24))
	{
		task_p->exec = bubble_child_exec;
	}
}

// FUNCTION: SADX 0x008d8f80
void bubble_child_draw(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	bubble_draw_sprite(&local_8->pos, (struct NJS_ARGB *)0, local_8->scl.x, *(float *)((char *)local_8 + 0x30) * local_8->scl.x);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x008d92b0
void bubble_small_draw(struct task *bbls_task_p)
{
}

// FUNCTION: SADX 0x008d93d0
void bubble_small_end(struct task *bbls_task_p)
{
	FUN_008d97e0(bbls_task_p->twp);
}

// STUB: SADX 0x008d93f0
int FUN_008d93f0(float *param_1)
{
	return (int)0;
}

// STUB: SADX 0x008d94c0
void FUN_008d94c0(struct taskwk *twp, int num)
{
}

// STUB: SADX 0x008d95b0
void bubble_small_new_work(struct bbl_small_taskwk *bbls_taskwk_p, float x, float z)
{
}

// STUB: SADX 0x008d9740
struct o_bubble *FUN_008d9740(struct o_bubble *param_1, struct o_bubble *param_2)
{
	return (struct o_bubble *)0;
}

// STUB: SADX 0x008d97e0
void FUN_008d97e0(struct taskwk *twp)
{
}

// STUB: SADX 0x008d9820
void FUN_008d9820(int param_1, float *param_2, int *param_3, float param_4, float param_5, float param_6, float param_7)
{
}

// FUNCTION: SADX 0x008d98c0
void bubble_draw_sprite(struct NJS_POINT3 *pos_p, struct NJS_ARGB *argb_p, float scale_x, float scale_y)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (argb_p == NULL)
	{
		argb_p = &default_argb;
	}
	___njSetConstantMaterial(argb_p);
	sprite_o_bubble.p = *pos_p;
	sprite_o_bubble.sx = scale_x * 0.03125f;
	sprite_o_bubble.sy = scale_y * 0.03125f;
	___njDrawSprite3D(&sprite_o_bubble, 0, 0x32);
	ResetMaterial();
}

// STUB: SADX 0x008d9b10
int FUN_008d9b10(int param_1, void *param_2, float param_3, float param_4, float param_5)
{
	return (int)0;
}

// STUB: SADX 0x008d9d80
void FUN_008d9d80(float *param_1)
{
}

// STUB: SADX 0x008d9e40
void FUN_008d9e40(struct task *task_p)
{
}

// STUB: SADX 0x008d9f50
void FUN_008d9f50(struct task *tp)
{
}

// STUB: SADX 0x008da020
void bbl_ripple_set(struct NJS_POINT3 *pos_p, float speed, float fade, float size)
{
}

// STUB: SADX 0x008da0e0
void bbl_ripple_exec(struct task *task_p)
{
}

// STUB: SADX 0x008da1a0
void bbl_ripple_draw(struct task *task_p)
{
}
