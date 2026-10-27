#include "decls.h"
#include <stdarg.h>
#include <stdio.h>
extern char DAT_05edd2e0[0x400];

// FUNCTION: SADX 0x005e2870
int DebPrintf(int loc, const char *format, ...)
{
	va_list local_cg;
	int local_8g;
	va_start(local_cg, format);
	local_8g = vsprintf(DAT_05edd2e0, format, local_cg);
	va_end(local_cg);
	njPrintC(loc, DAT_05edd2e0);
	return local_8g;
}
