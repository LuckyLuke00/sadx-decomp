#include "decls.h"

// STUB: SADX 0x00435270
void _pdVibMxInit(void)
{
}

// FUNCTION: SADX 0x004352a0
void _pdVibMxFinish(void)
{
	njDeleteWaitVSyncFunc(_pdVibMxServer);
}

// STUB: SADX 0x004352b0
void pdVibMxStart(int param_1, int *param_2)
{
}

// STUB: SADX 0x00435370
void pdVibMxStop(int param_1)
{
}
