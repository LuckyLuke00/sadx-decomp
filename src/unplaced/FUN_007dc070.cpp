#include "decls.h"
extern struct task *DAT_060ccb48;

// STUB: SADX 0x007dc070
void FUN_007dc070(float param_1)
{
}

// FUNCTION: SADX 0x007dc090
void FUN_007dc090(float param_1, float param_2, float param_3)
{
	struct taskwk *var1;
	var1 = DAT_060ccb48->twp;
	var1->pos.x = param_1;
	var1->pos.y = param_2;
	var1->pos.z = param_3;
}

// FUNCTION: SADX 0x007dc0b0
void FUN_007dc0b0(void)
{
	struct taskwk *var1 = DAT_060ccb48->twp;
	float *var2 = (float *)var1->value.ptr;
	var2[2] = -30.0f;
	var2[10] = 1.0f;
	var2[11] = 1.0f;
	var2[12] = 1.0f;
	var2[13] = 0.6f;
	var1->mode = 3;
}
