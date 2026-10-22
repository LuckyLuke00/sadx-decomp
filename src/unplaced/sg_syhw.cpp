#include "decls.h"
void FUN_00429d40(void);
void syTmrInit(void);

// FUNCTION: SADX 0x00430e40
void syHwInit(void)
{
	FUN_00429d40();
	syTmrInit();
}

// FUNCTION: SADX 0x00430e50
void syHwFinish(void)
{
	stFinishVertex();
	stDirect3DFinish();
}
