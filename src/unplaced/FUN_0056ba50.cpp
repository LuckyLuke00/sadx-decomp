#include "decls.h"
void FUN_0056a200(struct task *param_1);

// FUNCTION: SADX 0x0056ba50
void FUN_0056ba50(struct task *param_1, float param_2, float param_3, float param_4)
{
	struct taskwk *local_8g;
	if (param_1 != 0)
	{
		local_8g = *(struct taskwk **)((char *)param_1->twp + 0x3c);
		FUN_0056a200(param_1);
		*(unsigned char *)((char *)local_8g + 0x24) = 2;
		*(float *)((char *)local_8g + 0x28) = param_2;
		*(float *)((char *)local_8g + 0x2c) = param_3;
		*(float *)((char *)local_8g + 0x30) = param_4;
		*(float *)((char *)local_8g + 0x34) = 0.0f;
		*(float *)((char *)local_8g + 0x38) = 0.0f;
	}
	return;
}
