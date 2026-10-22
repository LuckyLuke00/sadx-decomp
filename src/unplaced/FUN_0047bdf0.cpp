#include "decls.h"

// FUNCTION: SADX 0x0047be10
void FUN_0047be10(void *param_1)
{
	if (*(void **)((char *)param_1 + 0x30) != NULL)
	{
		Free(*(void **)((char *)param_1 + 0x30));
		*(void **)((char *)param_1 + 0x30) = NULL;
	}
}

// STUB: SADX 0x0047c660
int FUN_0047c660(void)
{
	return (int)0;
}
