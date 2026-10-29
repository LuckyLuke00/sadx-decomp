#include "decls.h"
extern int DAT_05ada118;

// FUNCTION: SADX 0x00432430
int *pdMouseGetButton(int port)
{
	return &DAT_05ada118 + port * 6;
}

// STUB: SADX 0x00432450
int *pdMouseGetAxis(int port)
{
	return (int *)0;
}
