#include "decls.h"
extern struct TaskInfo DAT_00a09c28;
extern struct task *DAT_060cd274;

// FUNCTION: SADX 0x007e5000
void CartRaceDestroyManageTask()
{
	if (DAT_060cd274)
	{
		DestroyTask(DAT_060cd274);
		DAT_060cd274 = 0;
	}
}

// STUB: SADX 0x007e5020
void CartRacePrepareRace()
{
}

// FUNCTION: SADX 0x007e5050
signed char CartRaceGetMode()
{
	signed char var1 = 0;
	if (DAT_060cd274 != 0)
	{
		var1 = ((struct taskwk *)DAT_060cd274->mwp)->mode;
	}
	return var1;
}

// FUNCTION: SADX 0x007e5070
signed char CartRaceGetDialState()
{
	signed char var1 = 0;
	if (DAT_060cd274 != 0)
	{
		var1 = *(signed char *)((char *)DAT_060cd274->mwp + 3);
	}
	return var1;
}

// STUB: SADX 0x007e5320
long CartRaceInitTime()
{
	return (long)0;
}

// FUNCTION: SADX 0x007e54d0
void initRace(struct task *task_p, const void *param_p)
{
	CartInitLetter();
	DAT_060cd274 = task_p;
	CartRaceInitTime();
}

// FUNCTION: SADX 0x007e5600
struct task *CartRaceSetManageTask()
{
	return MirenSetTask((enum tasklevel)2, &DAT_00a09c28, 0);
}
