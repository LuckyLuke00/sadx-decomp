#include "decls.h"
static void Initial(struct task *tp);

// FUNCTION: SADX 0x00856630
static void Initial(struct task *tp)
{
	switch (tp->twp->mode)
	{
		case 0:
			CCL_Init(tp, object_c_info, 4, 2);
			break;
		case 1:
			CCL_Init(tp, &object_c_info[1], 4, 1);
			break;
		case 2:
			CCL_Init(tp, &object_c_info[2], 4, 1);
			break;
		case 3:
			CCL_Init(tp, &object_c_info[3], 4, 1);
			break;
	}
	tp->exec = Normal;
	tp->disp = Normal;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x008566a0
void ObjectHasira1(struct task *tp)
{
	tp->twp->mode = 0;
	Initial(tp);
}

// FUNCTION: SADX 0x008566c0
void ObjectHasira2(struct task *tp)
{
	tp->twp->mode = 1;
	Initial(tp);
}

// FUNCTION: SADX 0x008566e0
void ObjectSekicyuu(struct task *tp)
{
	tp->twp->mode = 2;
	Initial(tp);
}

// FUNCTION: SADX 0x00856700
void ObjectTerasu(struct task *tp)
{
	tp->twp->mode = 3;
	Initial(tp);
}
