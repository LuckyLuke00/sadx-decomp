#include "decls.h"

// FUNCTION: SADX 0x005b2480
void FUN_005b2480(int param_1)
{
	if (*(struct eventwk **)(param_1 + 0x3c) != 0)
	{
		FreeEventAction((struct taskwk *)param_1);
		FreeEventPath((struct taskwk *)param_1);
		Free(*(void **)(param_1 + 0x3c));
		*(void **)(param_1 + 0x3c) = 0;
	}
}
