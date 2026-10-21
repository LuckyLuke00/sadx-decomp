#include "decls.h"

// FUNCTION: SADX 0x00422e40
void FUN_00422e40(void *param_1)
{
	_gjSwapBuffers();
}

// FUNCTION: SADX 0x00422e50
void FUN_00422e50(void *param_1)
{
	_gjRenderClear();
}

// FUNCTION: SADX 0x00422e60
void FUN_00422e60(void *param_1)
{
	_gjBeforeRender();
}

// FUNCTION: SADX 0x00422e70
void FUN_00422e70(void *param_1)
{
	_gjWaitVsync();
}
