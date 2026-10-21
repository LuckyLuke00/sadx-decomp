#include "decls.h"
extern struct task *DAT_05edc12c;

// FUNCTION: SADX 0x005b9950
void FUN_005b9950(struct AlrReal *param_1)
{
	E102Hit_Exit();
}

// FUNCTION: SADX 0x005b9960
void E102Hit_Exit()
{
	if (DAT_05edc12c != 0)
	{
		FreeTask(DAT_05edc12c);
		DAT_05edc12c = 0;
	}
}

// STUB: SADX 0x005b9990
void E102Hit(struct NJS_POINT3 *pPos, float fOffsetZ)
{
}
