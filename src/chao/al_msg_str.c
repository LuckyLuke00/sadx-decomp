#include "decls.h"

extern int DAT_05b3ebbc;

// STUB: SADX 0x0044c4c0
int AlMsgStrEmbed(char *dst, const char *format, const char * *suite)
{
	return (int)0;
}

// FUNCTION: SADX 0x0044c520
const unsigned long *AlMsgStrLoad(const char *name)
{
	return AlMsgStrLoadLang(name, DAT_05b3ebbc);
}
