#include "decls.h"
extern struct obj object_snow_saku02_b_saku02_b[];
extern struct obj object_snow_saku02_saku02[];
extern struct obj object_snow_saku01_b_saku01_b[];

// GLOBAL: SADX 0x045dabf8
static struct CCL_INFO object_c_info[1];

extern struct obj object_snow_saku01_saku01[];

// FUNCTION: SADX 0x00866d10
void ObjectSaku01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	*(struct obj **)((char *)var1 + 8) = object_snow_saku01_saku01;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866d40
void ObjectSaku01b(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	*(struct obj **)((char *)var1 + 8) = object_snow_saku01_b_saku01_b;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866d70
void ObjectSaku02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	*(struct obj **)((char *)var1 + 8) = object_snow_saku02_saku02;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866da0
void ObjectSaku02b(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	*(struct obj **)((char *)var1 + 8) = object_snow_saku02_b_saku02_b;
	ObjectCCollision(tp);
}
