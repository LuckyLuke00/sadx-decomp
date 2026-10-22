#include "decls.h"
extern int DAT_05ada118;

// FUNCTION: SADX 0x00432430
int *pdMouseGetButton(int param_1)
{
	return &DAT_05ada118 + param_1 * 6;
}

// STUB: SADX 0x00432450
int *pdMouseGetAxis(int param_1)
{
	return (int *)0;
}
