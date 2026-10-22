#include "decls.h"

// STUB: SADX 0x006b56e0
void FUN_006b56e0(struct obj *obj)
{
}

// FUNCTION: SADX 0x006b5760
void FUN_006b5760(void *param_1)
{
	void *var1 = *(void **)((char *)param_1 + 0x20);
	Free(*(void **)((char *)var1 + 0x10));
	Free(*(void **)((char *)var1 + 0xc));
}
