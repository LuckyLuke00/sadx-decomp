#include "decls.h"
#include <stdarg.h>
#include <stdio.h>
extern char DAT_05edd2e0[0x800];

// FUNCTION: SADX 0x005e2870
int DebPrintf(int loc, const char *format, ...)
{
	va_list local_8g;
	int local_cg;
	va_start(local_8g, format);
	local_cg = vsprintf(DAT_05edd2e0, format, local_8g);
	njPrintC(loc, DAT_05edd2e0);
	return local_cg;
}
