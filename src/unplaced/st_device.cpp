#include "decls.h"
extern unsigned int DAT_01c6e418;

// FUNCTION: SADX 0x00419690
void _stCreateDevice(void)
{
	SOCCreateDevice();
}

// FUNCTION: SADX 0x004196a0
void _stSetDepthHigh(void)
{
	DAT_01c6e418 = 0x1c6e3f4;
}
