#include "decls.h"
extern short DAT_05b9d744;
extern unsigned char DAT_060cd268;

// FUNCTION: SADX 0x007e4ca0
void CartActInitActDiff()
{
	DAT_060cd268 = 0;
}

// FUNCTION: SADX 0x007e4cb0
int CartActGetActDiff()
{
	return (char)DAT_060cd268;
}

// FUNCTION: SADX 0x007e4cc0
void initControlAct(struct task *task_p, const struct CtrlActParam *param_p)
{
	char *var1 = (char *)task_p->mwp;
	char var2 = (char)DAT_05b9d744;

	var1[0] = var2;
	var1[1] = var2;
	var1[2] = 6;
	*(short *)(var1 + 4) = *(short *)param_p;
	*(short *)(var1 + 6) = *(short *)((char *)param_p + 2);
}

// STUB: SADX 0x007e4e00
signed char decideAct(struct task *task_p)
{
	return (signed char)0;
}
