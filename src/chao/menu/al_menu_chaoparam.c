#include "decls.h"
extern int DAT_060cb320;

// STUB: SADX 0x00716200
void AL_ChaoParamWindowDestructor(struct task *tp)
{
}

// FUNCTION: SADX 0x00716300
void AL_DrawStopChaoParamWindow(int flag)
{
	DAT_060cb320 = flag;
}
