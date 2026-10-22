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

// STUB: SADX 0x007e5050
signed char CartRaceGetMode()
{
	return (signed char)0;
}

// STUB: SADX 0x007e5070
signed char CartRaceGetDialState()
{
	return (signed char)0;
}

// STUB: SADX 0x007e5320
long CartRaceInitTime()
{
	return (long)0;
}

// STUB: SADX 0x007e54d0
void initRace(struct task *task_p, const void *param_p)
{
}

// FUNCTION: SADX 0x007e5600
struct task *CartRaceSetManageTask()
{
	return MirenSetTask((enum tasklevel)2, &DAT_00a09c28, 0);
}
