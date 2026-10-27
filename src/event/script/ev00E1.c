#include "decls.h"
extern struct TEX_PVMTABLE DAT_060cb684[];
static void evmain(int code);
extern char DAT_009d4890[];

// FUNCTION: SADX 0x00734c60
static void evmain(int code)
{
	if (code - 1)
	{
		return;
	}
	EV_MsgW(0x5a, (char *)&DAT_009d4890);
}

// GLOBAL: SADX 0x02c23890
struct EVTABLE2 __ev00e1 = {evmain, DAT_060cb684};
