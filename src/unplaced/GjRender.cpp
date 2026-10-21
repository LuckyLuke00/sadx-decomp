#include "decls.h"
void stHWWaitVSync();

// FUNCTION: SADX 0x00430700
void _gjWaitVsync(void)
{
	stHWWaitVSync();
}
