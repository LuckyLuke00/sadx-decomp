#include "decls.h"
extern char DAT_009e1668[1];
extern struct TEX_PVMTABLE DAT_060cb8ac[];
static void evmain(int code);

// FUNCTION: SADX 0x00758250
static void evmain(int code)
{
	if (--code)
	{
		return;
	}
	EV_MsgW(0x5a, (char *)&DAT_009e1668);
}

// GLOBAL: SADX 0x02c29870
struct EVTABLE2 __ev009c = {evmain, DAT_060cb8ac};
