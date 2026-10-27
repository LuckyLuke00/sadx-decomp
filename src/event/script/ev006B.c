#include "decls.h"
extern char DAT_009ec7a8[1];
extern struct TEX_PVMTABLE DAT_060cba24[];
static void evmain(int code);

// FUNCTION: SADX 0x007738d0
static void evmain(int code)
{
	if (code - 1 == 0)
	{
		EV_MsgW(0x5a, DAT_009ec7a8);
	}
}

// GLOBAL: SADX 0x02c2ff30
struct EVTABLE2 DAT_02c2ff30 = {evmain, DAT_060cba24};
