#include "decls.h"

#pragma optimize("", off)
// STUB: SADX 0x004351c0
void _pdVibMxServer(void)
{
}
#pragma optimize("", on)

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
void pdVibMxStart(int port, int *param)
{
}

// STUB: SADX 0x00435370
void pdVibMxStop(int port)
{
}
