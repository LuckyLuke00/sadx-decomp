#include "decls.h"
void FUN_0044e380(struct DAT_0044e380_0 *param_1, int param_2, int param_3, int param_4);

// STUB: SADX 0x0044e1d0
void AlMsgWinCreate(struct SAlMsgWin *self)
{
}

// STUB: SADX 0x0044e210
void AlMsgWinDelete(struct SAlMsgWin *self)
{
}

// FUNCTION: SADX 0x0044e2a0
void AlMsgWinSetPos(struct SAlMsgWin *self, float px, float py, float pz)
{
	*(float *)((char *)self + 0x10) = px;
	*(float *)((char *)self + 0x14) = py;
	*(float *)((char *)self + 0xc) = pz;
}

// FUNCTION: SADX 0x0044e2c0
void AlMsgWinSetSize(struct SAlMsgWin *self, float sx, float sy)
{
	*(float *)((char *)self + 0x18) = sx;
	*(float *)((char *)self + 0x1c) = sy;
}

// FUNCTION: SADX 0x0044e2e0
void FUN_0044e2e0(int param_1, int param_2)
{
	*(int *)(param_1 + 0x2c) = param_2;
}

// FUNCTION: SADX 0x0044e2f0
int FUN_0044e2f0(int param_1)
{
	return *(short *)((char *)param_1 + 0xa) > 0;
}

// STUB: SADX 0x0044e330
void FUN_0044e330(struct SAlMsgWin *param_1, int param_2, int param_3, float param_4, float param_5, float param_6, float param_7, float param_8, float param_9)
{
}

// STUB: SADX 0x0044e380
void FUN_0044e380(struct DAT_0044e380_0 *param_1, int param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x0044e3e0
void AlMsgWinWaitCont(struct SAlMsgWin *self)
{
}

// STUB: SADX 0x0044e400
void AlMsgWinWaitCont2(struct SAlMsgWin *self, unsigned long ke, unsigned long ko)
{
}

// STUB: SADX 0x0044e420
void AlMsgWinWaitClose(struct SAlMsgWin *self)
{
}

// STUB: SADX 0x0044e440
void AlMsgWinWaitClose2(struct SAlMsgWin *self, unsigned long ke, unsigned long ko)
{
}

// STUB: SADX 0x0044e460
void FUN_0044e460(float param_1, const char *param_2, long param_3)
{
}
