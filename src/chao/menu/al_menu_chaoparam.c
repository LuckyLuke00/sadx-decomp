#include "decls.h"
void FreeTask(struct task *tp);
void Free(void *mp);
extern int DAT_060cb324;
extern int DAT_060cb320;

// FUNCTION: SADX 0x00716200
void AL_ChaoParamWindowDestructor(struct task *tp)
{
	struct anywk *var1 = tp->awp;
	struct task *var2 = (struct task *)*(void **)((char *)var1 + 0x38);

	DAT_060cb320 = 0;
	if (var2 != 0)
	{
		FreeTask(var2);
		*(void **)((char *)var1 + 0x38) = 0;
	}
	if (tp->awp != 0)
	{
		Free(tp->awp);
		tp->awp = 0;
	}
	DAT_060cb324 = 0;
}

// STUB: SADX 0x00716250
void AL_CreateChaoParamWindow(float xpos, float ypos)
{
}

// FUNCTION: SADX 0x00716300
void AL_DrawStopChaoParamWindow(int flag)
{
	DAT_060cb320 = flag;
}
