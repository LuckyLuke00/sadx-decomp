#include "decls.h"
void InitContinueData();

// STUB: SADX 0x005a5490
void InitContinueData()
{
}

// STUB: SADX 0x005a54d0
long CheckContinueData()
{
	return (long)0;
}

// STUB: SADX 0x005a5500
void RestoreContinueData(struct NJS_POINT3 *pos, struct Angle3 *ang)
{
}

// STUB: SADX 0x005a55e0
void updateContinueData(struct NJS_POINT3 *pos, struct Angle3 *ang)
{
}

// FUNCTION: SADX 0x005a58c0
void savepointExit(struct task *tp)
{
	if (tp->awp->work.ptr[0] != 0)
	{
		Free(tp->awp->work.ptr[0]);
		tp->awp->work.ptr[0] = 0;
	}
}

// STUB: SADX 0x005a58f0
void savepointDisplay(struct task *tp)
{
}

// STUB: SADX 0x005a5a20
void *FUN_005a5a20()
{
	return (void *)0;
}

// STUB: SADX 0x005a5a70
void rotateBall(struct obj *obj)
{
}

// STUB: SADX 0x005a5cf0
void FUN_005a5cf0(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x005a60a0
void savepointPrintLaptime(struct task *tp, struct taskwk *twp)
{
}
