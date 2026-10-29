#include "decls.h"
float njSin(int param_1);
void FUN_008babc0(struct obj *param_1);
void FUN_008bac40(struct taskwk *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bae10(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008babc0(struct obj *param_1);
void FUN_008bac40(struct taskwk *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bae10(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bb1a0(void *param_1);
void BaloonScale(struct taskwk *twp);
float njSin(int);
void FUN_008babc0(struct obj *param_1);
void FUN_008bad70(struct obj *param_1);
void FUN_008bae10(struct obj *param_1);

// STUB: SADX 0x008baad0
void ObjectBaloon(struct task *tp)
{
}

// STUB: SADX 0x008babc0
void FUN_008babc0(struct obj *param_1)
{
}

// STUB: SADX 0x008bac40
void FUN_008bac40(struct taskwk *param_1)
{
}

// STUB: SADX 0x008bad70
void FUN_008bad70(struct obj *param_1)
{
}

// STUB: SADX 0x008bae10
void FUN_008bae10(struct obj *param_1)
{
}

// FUNCTION: SADX 0x008bb170
void FUN_008bb170(int param_1)
{
	*(float *)(param_1 + 0x10) = njSin((*(int *)(param_1 + 8) + 0x320) << 8) * 4.0;
}

// FUNCTION: SADX 0x008bb1a0
void FUN_008bb1a0(void *param_1)
{
	*(int *)((char *)param_1 + 0x1c) = (int)(njCos((*(int *)((char *)param_1 + 8) + 0x7d0) * 0xc8) * 4096.0);
}

// FUNCTION: SADX 0x008bb1e0
void BaloonScale(struct taskwk *twp)
{
	twp->scl.x = 1.0f - njCos(twp->counter.l << 0xb) * 0.05000000074505806;
	twp->scl.y = 1.0f - njSin(twp->counter.l << 0xb) * 0.05000000074505806;
}
