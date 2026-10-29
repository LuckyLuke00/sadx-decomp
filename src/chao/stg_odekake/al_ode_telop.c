#include "decls.h"
extern struct task *DAT_05b33104;
void FreeTask(struct task *tp);

// STUB: SADX 0x00481920
void AL_OdeTelopCreate()
{
}

// FUNCTION: SADX 0x00481a10
void AL_OdeTelopDelete()
{
	FreeTask(DAT_05b33104);
}

// FUNCTION: SADX 0x00481a20
void FUN_00481a20()
{
	AlMsgTelopClear((struct SAlMsgTelop *)DAT_05b33104->awp->work.ptr[0]);
}

// STUB: SADX 0x00481a40
void AL_OdeTelopClear()
{
}

// STUB: SADX 0x004820e0
void AL_OdeTelopAdd(int param_1, float param_2, short param_3, int param_4, float param_5)
{
}
