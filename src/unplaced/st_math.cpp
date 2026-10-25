#include "decls.h"
extern void *DAT_05ab39ac;
extern int DAT_01c6e760;
void FUN_0041a620(void *param_1);

// STUB: SADX 0x0042b570
void stSetMatrixLocalToCamera(void)
{
}

// FUNCTION: SADX 0x0042b590
void stResetMatrix(void)
{
	__asm {
		mov ecx, dword ptr [DAT_05ab39ac]
		push offset DAT_01c6e760
		call FUN_0041a620
	}
}
