#include "decls.h"
#include "../advertise.h"

extern int DAT_05ab42a0;
extern int DAT_05ab42a4;

// STUB: SADX 0x0041b2d0
void SOCRender::UIShaderSet()
{
}

// FUNCTION: SADX 0x0041b450
void FUN_0041b450(int param_1)
{
	DAT_05ab42a0 = param_1;
	DAT_05ab42a4 = FUN_0041a800()->FUN_004caf80();
}

