#include "decls.h"
struct GJS_PRINTBUF;
extern struct NJS_TEXLIST DAT_01c76eb0;

// STUB: SADX 0x004315a0
void gjPrint(struct GJS_PRINTBUF const *param_1)
{
}

// STUB: SADX 0x004316f0
void gjPrintInit(void *param_1, unsigned long param_2, unsigned long param_3)
{
}

// FUNCTION: SADX 0x00431730
void gjPrintExit(void)
{
	njReleaseTexture(&DAT_01c76eb0);
}
