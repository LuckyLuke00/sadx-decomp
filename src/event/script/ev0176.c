#include "decls.h"
extern struct TEX_PVMTABLE DAT_060cb378[];
static void evmain(int code);

// FUNCTION: SADX 0x007188d0
static void evmain(int code)
{
	switch (code)
	{
	case 1:
		FUN_0056bb90();
		FUN_0056a2b0();
		FUN_0056a2c0();
		FUN_0056b370(FUN_0056b1f0(0), -528.0f, 0.0f, 1312.0f);
		EV_CameraAng(1, 0, 0xeb00, 0x7600, 0);
		EV_CameraPos(1, 0, -677.5f, 33.0f, 1268.72f);
		BGM_Play(0x38);
		FUN_0056aea0(0x55);
		return;
	case 2:
		FUN_0056bcd0();
		FUN_0056a2a0();
		return;
	}
}

// GLOBAL: SADX 0x02c19734
struct EVTABLE2 __ev0176 = {evmain, DAT_060cb378};
