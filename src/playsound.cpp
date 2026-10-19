#include "decls.h"

extern int DAT_05b3dfc0;

// FUNCTION: SADX 0x004ab0b0
bool FUN_004ab0b0()
{
	return true;
}

// FUNCTION: SADX 0x004ab0c0
bool EndPlaySound()
{
	wmaend();
	return true;
}

// FUNCTION: SADX 0x004ab0d0
void Set3Dmode(int flag)
{
	DAT_05b3dfc0 = flag;
}

// FUNCTION: SADX 0x004ab0e0
int Get3Dmode()
{
	return DAT_05b3dfc0;
}
