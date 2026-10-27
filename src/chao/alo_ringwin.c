#include "decls.h"
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
void ALO_RingWinAdd(long num);
void ALO_RingWinSetPos(float px, float py, unsigned long flag);
extern float DAT_060c60c0;
extern float DAT_060c60c4;
extern long DAT_060c60cc;
extern struct task *DAT_060c60ec;

// STUB: SADX 0x00710a10
long DigitsToInt(const signed char *dig)
{
	return (long)0;
}

// FUNCTION: SADX 0x007110e0
void ALO_RingWinDelete()
{
	if (DAT_060c60ec)
	{
		FreeTask(DAT_060c60ec);
		DAT_060c60ec = 0;
	}
}

// FUNCTION: SADX 0x00711140
void FUN_00711140(long param_1)
{
	ALO_RingWinAdd(DAT_060c60cc + param_1);
}

// FUNCTION: SADX 0x00711160
void ALO_RingWinSetPos(float px, float py, unsigned long flag)
{
	if (flag & 1)
	{
		px = px - 94.0;
	}
	else if (flag & 2)
	{
		px = px - 188.0;
	}
	if (flag & 4)
	{
		py = py - 94.0;
	}
	else if (flag & 8)
	{
		py = py - 40.0;
	}
	DAT_060c60c0 = px;
	DAT_060c60c4 = py;
}

// FUNCTION: SADX 0x007111c0
void ALO_RingWinCreate(float px, float py, unsigned long flag)
{
	memset(&DAT_060c60c0, 0, 0x2c);
	DAT_060c60ec = CreateElementalTask(0, 3, FTaskExec);
	ALO_RingWinSetPos(px, py, flag);
}
