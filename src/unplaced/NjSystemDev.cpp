#include "decls.h"
void stHWSetVSync(int param_1);

// STUB: SADX 0x004224d0
void njColorBlendingMode(Int param_1, Int param_2)
{
}

// STUB: SADX 0x00422540
void gjGXSetBlendMode(long param_1)
{
}

// STUB: SADX 0x00422590
void njSetZUpdateMode(long param_1)
{
}

// FUNCTION: SADX 0x004225b0
void njSetWaitVsyncCount(Int param_1)
{
	stHWSetVSync(param_1);
}

// STUB: SADX 0x004225c0
void njPolygonCullingMode(Int param_1)
{
}
