#include "decls.h"
void stHWSetVSync(int param_1);

// STUB: SADX 0x004224d0
void njColorBlendingMode(int target, int mode)
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
void njSetWaitVsyncCount(int count)
{
	stHWSetVSync(count);
}

// STUB: SADX 0x004225c0
void njPolygonCullingMode(int mode)
{
}
