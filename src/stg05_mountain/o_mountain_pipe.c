#include "decls.h"
extern struct obj object_pipe_set_pipe_l_pipe_l[];
extern struct obj object_pipe_set_pipebox_pipebox[];
static struct CCL_INFO object_c_info[4];
extern struct obj object_pipe_set_pipe_i_pipe_i[];

// FUNCTION: SADX 0x00834760
void ObjectMountainPipeI(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_pipe_set_pipe_i_pipe_i;
	var1->value.ptr = &texlist_obj_mountain;
	if (var1->mode == 0)
	{
		CCL_Init(tp, &object_c_info[1], 1, 4);
	}
	CheckCollisionScale(var1);
	ObjectScaleCCollision(tp);
}

// FUNCTION: SADX 0x008347a0
void ObjectMountainPipeBox(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_pipe_set_pipebox_pipebox;
	var1->value.ptr = &texlist_obj_mountain;
	if (var1->mode == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
	}
	CheckCollisionScale(var1);
	ObjectScaleCCollision(tp);
}

// FUNCTION: SADX 0x008347e0
void ObjectMountainPipeL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_pipe_set_pipe_l_pipe_l;
	var1->value.ptr = &texlist_obj_mountain;
	if (var1->mode == 0)
	{
		CCL_Init(tp, object_c_info + 2, 2, 4);
		var1->mode = 1;
	}
	CheckCollisionScale(var1);
	ObjectScaleCCollision(tp);
}
