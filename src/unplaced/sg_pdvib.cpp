#include "decls.h"

// STUB: SADX 0x004351c0
void _pdVibMxServer(void)
{
}

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
Sint32 pdVibMxStop(Uint32 port)
{
	return (Sint32)0;
}
