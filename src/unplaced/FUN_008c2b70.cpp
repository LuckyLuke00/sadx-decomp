#include "decls.h"
extern void FUN_008c26f0(int param_1, int param_2, int param_3);

// FUNCTION: SADX 0x008c2b70
void FUN_008c2b70(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2, struct NJS_POINT3 *param_3, struct NJS_POINT3 *param_4)
{
	struct NJS_POINT3 local_20;
	struct NJS_POINT3 local_14;
	njCalcPoint(0, param_2, &local_20);
	njCalcPoint(0, param_3, &local_14);
	FUN_008c26f0((int)param_1, (int)&local_20, (int)param_4);
}

// STUB: SADX 0x008c2bd0
void FUN_008c2bd0(void)
{
}
