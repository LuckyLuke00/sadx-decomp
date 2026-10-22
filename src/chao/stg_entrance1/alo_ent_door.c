#include "decls.h"
extern int DAT_05b33014;

// FUNCTION: SADX 0x004720d0
void ALO_EntDoorOpen()
{
	*(char *)((char *)*(int *)((char *)DAT_05b33014 + 0x2c) + 0xf) = 1;
}
