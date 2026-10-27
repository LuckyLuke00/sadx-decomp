#include "decls.h"
extern char DAT_009f2c10[1];
extern struct TEX_PVMTABLE DAT_060cbb04[];
static void evmain(int code);

// FUNCTION: SADX 0x00789770
static void evmain(int code)
{
	if (--code)
		return;
	EV_MsgW(0x5a, (char *)&DAT_009f2c10);
}

// GLOBAL: SADX 0x02c33a64
struct EVTABLE2 DAT_02c33a64 = {evmain, DAT_060cbb04};
