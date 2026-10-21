#include "decls.h"
extern struct obj object_sky_obj_lift_a_obj_lift_a;

// FUNCTION: SADX 0x005c2e00
void AirLiftDestructor(struct task *tp)
{
	WithdrawCollisionEntry(tp, &object_sky_obj_lift_a_obj_lift_a);
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x005c2fb0
void FUN_005c2fb0(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	AirLiftDraw(param_1);
}

// STUB: SADX 0x005c34a0
void FUN_005c34a0(void *param_1)
{
}

// FUNCTION: SADX 0x005c35b0
void FUN_005c35b0(int param_1, int param_2)
{
	int local_cg;
	int local_8g;

	local_cg = *(int *)((char *)param_1 + 0x20);
	local_8g = *(int *)((char *)*(int *)((char *)param_1 + 8) + 0x20);
	if (*(char *)local_8g == 7)
	{
		*(char *)(param_2 + 0x49) = *(char *)local_cg;
		*(char *)local_cg = 1;
		*(short *)((char *)local_cg + 6) = 0;
	}
}

// FUNCTION: SADX 0x005c3f90
void FUN_005c3f90(struct taskwk *param_1, struct enemywk *param_2)
{
	MissleBombDraw(param_1, param_2);
	EntryColliList(param_1);
}

// STUB: SADX 0x005c4350
void FUN_005c4350(struct task *tp, int param_2, int param_3)
{
}

// STUB: SADX 0x005c5830
void FUN_005c5830(struct task *param_1)
{
}
