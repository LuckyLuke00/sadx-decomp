#include "decls.h"
extern struct obj object_kareki_all1_ktree03_ktree03[];
extern struct obj object_kareki_all1_ktree02_ktree02[];

// GLOBAL: SADX 0x045daa48
static struct CCL_INFO object_c_info[3];

extern struct obj object_kareki_all1_ktree01_ktree01[];

// FUNCTION: SADX 0x00866430
void ObjectKareki01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_kareki_all1_ktree01_ktree01;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866460
void ObjectKareki02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_kareki_all1_ktree02_ktree02;
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00866490
void ObjectKareki03(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_kareki_all1_ktree03_ktree03;
	ObjectCCollision(tp);
}
