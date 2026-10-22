#include "decls.h"

// STUB: SADX 0x008babc0
void FUN_008babc0(struct obj *obj)
{
}

// FUNCTION: SADX 0x008bb170
void FUN_008bb170(int param_1)
{
	*(float *)(param_1 + 0x10) = njSin((*(int *)(param_1 + 8) + 0x320) << 8) * 4.0;
}

// STUB: SADX 0x008bb1a0
void FUN_008bb1a0(void *p)
{
}

// FUNCTION: SADX 0x008bb1e0
void BaloonScale(struct taskwk *twp)
{
	twp->scl.x = 1.0f - njCos(twp->counter.l << 0xb) * 0.05000000074505806;
	twp->scl.y = 1.0f - njSin(twp->counter.l << 0xb) * 0.05000000074505806;
}
