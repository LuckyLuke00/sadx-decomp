#include "decls.h"
void FUN_004c3310(int *param_1);
void syFree(void *param_1);
void drawmessage(struct ALERT_TASK_WORK *wk);
extern void *DAT_05cda188;

// STUB: SADX 0x0059c810
void AlertWindowTask(struct task *tp)
{
}

// STUB: SADX 0x0059ca00
void drawmessage(struct ALERT_TASK_WORK *wk)
{
}

// STUB: SADX 0x0059cc00
struct task *OpenAlertWindow(int level, struct ALERT_PARAM *Param)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x0059cdb0
void AlertWindowDestructor(struct task *tp)
{
	struct anywk *local_8;

	local_8 = tp->awp;
	if (*(int *)((char *)local_8 + 0x54) != 0)
	{
		FUN_004c3310((int *)((char *)local_8 + 0x2c));
		if (DAT_05cda188 != 0)
		{
			syFree(DAT_05cda188);
			DAT_05cda188 = 0;
		}
	}
}

// STUB: SADX 0x0059ce00
long CloseAlertWindow(struct task *tp)
{
	return (long)0;
}
