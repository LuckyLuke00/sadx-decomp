#include "decls.h"
extern unsigned char DAT_060cd268;

// FUNCTION: SADX 0x007e4ca0
void CartActInitActDiff()
{
	DAT_060cd268 = 0;
}

// STUB: SADX 0x007e4cb0
int CartActGetActDiff()
{
	return (int)0;
}

// STUB: SADX 0x007e4cc0
void initControlAct(struct task *task_p, const struct CtrlActParam *param_p)
{
}

// STUB: SADX 0x007e4e00
signed char decideAct(struct task *task_p)
{
	return (signed char)0;
}
