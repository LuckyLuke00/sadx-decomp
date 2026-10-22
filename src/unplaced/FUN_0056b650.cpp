#include "decls.h"

// FUNCTION: SADX 0x0056b650
void FUN_0056b650(struct task *param_1, struct NJS_ACTION *param_2, struct NJS_TEXLIST *param_3, float param_4, int param_5, int param_6)
{
	if (param_1 != 0)
	{
		EntryEventAction(param_1->twp, param_2, param_3, param_4, param_5, param_6);
	}
}

// STUB: SADX 0x0056b690
void FUN_0056b690(struct task *param_1, int param_2, int param_3, int param_4, float param_5, int param_6, int param_7, int param_8)
{
}

// FUNCTION: SADX 0x0056b6d0
void FUN_0056b6d0(struct task *param_1)
{
	if (param_1 != 0)
	{
		FreeEventAction(param_1->twp);
	}
}
