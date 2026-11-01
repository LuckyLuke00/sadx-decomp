#include "decls.h"
extern int DAT_05ada448[24];

// STUB: SADX 0x004351c0
void _pdVibMxServer(void)
{
}

// FUNCTION: SADX 0x00435270
void _pdVibMxInit(void)
{
	int var1;
	int *var2;
	var2 = (int *)&DAT_05ada448;
	for (var1 = 4; var1 != 0; var1--)
	{
		*var2 = 0;
		var2 += 6;
	}
	njEntryWaitVSyncFunc(_pdVibMxServer);
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
