#include "decls.h"
extern struct obj object_snow_fiw_6m_fiw_6m[1];
extern struct obj object_snow_fiw_5m_fiw_5m[];
extern struct obj object_snow_fiw_4m_fiw_4m[];

// GLOBAL: SADX 0x045dac28
static struct CCL_INFO object_c_info[4];

extern struct obj object_obj_ele_obj_ele[];

// FUNCTION: SADX 0x00866dd0
void ObjectEle(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_obj_ele_obj_ele;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866e00
void ObjectFiw4m(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[1], 1, 4);
	var1->counter.ptr = object_snow_fiw_4m_fiw_4m;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866e30
void ObjectFiw5m(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[2], 1, 4);
	var1->counter.ptr = object_snow_fiw_5m_fiw_5m;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866e60
void ObjectFiw6m(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, &object_c_info[3], 1, 4);
	var1->counter.ptr = object_snow_fiw_6m_fiw_6m;
	ObjectCCollision(tp);
}
