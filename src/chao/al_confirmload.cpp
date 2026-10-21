#include "decls.h"
extern int DAT_05b288a0;
extern int DAT_05b2889c;

// FUNCTION: SADX 0x00442db0
long AL_ConfirmLoadIsBusy()
{
	return DAT_05b2889c;
}

// FUNCTION: SADX 0x00442dc0
long AL_ConfirmLoadIsLoaded()
{
	return DAT_05b288a0;
}
