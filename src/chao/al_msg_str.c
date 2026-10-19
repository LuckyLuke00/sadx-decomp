#include "decls.h"

extern int DAT_05b3ebbc;

// FUNCTION: SADX 0x0044c520
const unsigned long *AlMsgStrLoad(const char *name)
{
	return AlMsgStrLoadLang(name, DAT_05b3ebbc);
}
